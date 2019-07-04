//------------------------------------------------------------------------------
//  cgltf-sapp.c
//
//  A simple(!) GLTF viewer, cgltf + sokol_app.h + sokol_gfx.h + sokol_fetch.h.
//  Doesn't support all GLTF features.
//
//  https://github.com/jkuhlmann/cgltf
//------------------------------------------------------------------------------
#define HANDMADE_MATH_IMPLEMENTATION
#define HANDMADE_MATH_NO_SSE
#include "HandmadeMath.h"
#include "sokol_gfx.h"
#include "sokol_app.h"
#include "sokol_audio.h"
#include "sokol_fetch.h"
#include "dbgui/dbgui.h"
#include "cgltf-sapp.glsl.h"
#define CGLTF_IMPLEMENTATION
#include "stb/stb_image.h"
#include "cgltf/cgltf.h"
#include <assert.h>

#define SAMPLE_COUNT (4)
#define SCENE_MAX_BUFFERS (64)
#define SCENE_MAX_IMAGES (64)

typedef struct {
    sg_buffer_type type;
    int offset;
    int size;
    int gltf_buffer_index;
    sg_buffer buffer;
} buffer_t;

typedef struct {
    sg_filter min_filter;
    sg_filter mag_filter;
    sg_wrap wrap_s;
    sg_wrap wrap_t;
    int gltf_image_index;
    sg_image image;
} image_t;

typedef struct {
    int num_buffers;
    int num_images;
    buffer_t buffers[SCENE_MAX_BUFFERS];
    image_t images[SCENE_MAX_IMAGES];
} scene_t;

static const char* filename = "DamagedHelmet.gltf";

static void gltf_fetch_callback(const sfetch_response_t*);
static void gltf_buffer_fetch_callback(const sfetch_response_t*);
static void gltf_image_fetch_callback(const sfetch_response_t*);
static void gltf_parse(const void* ptr, uint64_t num_bytes);
static void gltf_parse_buffers(const cgltf_data* gltf);
static void gltf_parse_images(const cgltf_data* gltf);
static void create_sgbuffers_for_gltfbuffer(int gltf_buffer_index, const uint8_t* bytes, int num_bytes);
static void create_sgimages_for_gltfimage(int gltf_image_index, const uint8_t* bytes, int num_bytes);

static struct {
    bool failed;
    sg_pass_action pass_action;
    sg_pass_action failed_pass_action;
    scene_t scene;
} state;

static void init(void) {
    // setup sokol-gfx
    sg_setup(&(sg_desc){
        .gl_force_gles2 = true,
        .mtl_device = sapp_metal_get_device(),
        .mtl_renderpass_descriptor_cb = sapp_metal_get_renderpass_descriptor,
        .mtl_drawable_cb = sapp_metal_get_drawable,
        .d3d11_device = sapp_d3d11_get_device(),
        .d3d11_device_context = sapp_d3d11_get_device_context(),
        .d3d11_render_target_view_cb = sapp_d3d11_get_render_target_view,
        .d3d11_depth_stencil_view_cb = sapp_d3d11_get_depth_stencil_view
    });
    // setup the optional debugging UI
    __dbgui_setup(SAMPLE_COUNT);

    // setup sokol-fetch with 2 channels and 6 lanes per channel,
    // we'll use one channel for mesh data and the other for textures
    sfetch_setup(&(sfetch_desc_t){
        .max_requests = 32,
        .num_channels = 2,
        .num_lanes = 6
    });

    // normal background color, and a "load failed" background color
    state.pass_action = (sg_pass_action) {
        .colors[0] = { .action=SG_ACTION_CLEAR, .val={1.0f, 1.0f, 0.0f, 1.0f} }
    };
    state.failed_pass_action = (sg_pass_action) {
        .colors[0] = { .action=SG_ACTION_CLEAR, .val={1.0f, 0.0f, 0.0f, 1.0f} }
    };

    // start loading the base gltf file...
    sfetch_send(&(sfetch_request_t){
        .channel = 0,
        .path = filename,
        .callback = gltf_fetch_callback,
    });
}

static void frame(void) {
    // pump the sokol-fetch message queue
    sfetch_dowork();

    // render the scene
    sg_begin_default_pass(state.failed ? &state.failed_pass_action : &state.pass_action, sapp_width(), sapp_height());
    __dbgui_draw();
    sg_end_pass();
    sg_commit();
}

static void cleanup(void) {
    sfetch_shutdown();
    __dbgui_shutdown();
    sg_shutdown();
}

// load-callback for the GLTF base file
static void gltf_fetch_callback(const sfetch_response_t* response) {
    if (response->opened) {
        // allocate and bind buffer to load file into
        sfetch_bind_buffer(response->handle, malloc(response->content_size), response->content_size);
    }
    else if (response->fetched) {
        // file has been loaded, parse as GLTF
        gltf_parse(response->buffer_ptr, response->fetched_size);
    }
    if (response->finished) {
        // don't forget to free the buffer (note: it's valid to call free()
        // with a null pointer
        free(sfetch_unbind_buffer(response->handle));
        if (response->failed) {
            state.failed = true;
        }
    }
}

// load-callback for GLTF buffer files
typedef struct {
    cgltf_size buffer_index;
} gltf_buffer_fetch_userdata_t;

static void gltf_buffer_fetch_callback(const sfetch_response_t* response) {
    if (response->opened) {
        sfetch_bind_buffer(response->handle, malloc(response->content_size), response->content_size);
    }
    else if (response->fetched) {
        const gltf_buffer_fetch_userdata_t* user_data = (const gltf_buffer_fetch_userdata_t*)response->user_data;
        int gltf_buffer_index = (int)user_data->buffer_index;
        create_sgbuffers_for_gltfbuffer(
            gltf_buffer_index,
            (const uint8_t*)response->buffer_ptr,
            (int)response->fetched_size);
    }
    if (response->finished) {
        free(sfetch_unbind_buffer(response->handle));
        if (response->failed) {
            state.failed = true;
        }
    }
}

// load-callback for GLTF image files
typedef struct {
    cgltf_size image_index;
} gltf_image_fetch_userdata_t;

static void gltf_image_fetch_callback(const sfetch_response_t* response) {
    if (response->opened) {
        sfetch_bind_buffer(response->handle, malloc(response->content_size), response->content_size);
    }
    else if (response->fetched) {
        const gltf_image_fetch_userdata_t* user_data = (const gltf_image_fetch_userdata_t*)response->user_data;
        int gltf_image_index = (int)user_data->image_index;
        create_sgimages_for_gltfimage(
            gltf_image_index,
            (const uint8_t*)response->buffer_ptr,
            (int)response->fetched_size);
    }
    if (response->finished) {
        free(sfetch_unbind_buffer(response->handle));
        if (response->failed) {
            state.failed = true;
        }
    }
}

// load GLTF data from memory, build scene and issue resource fetch requests
static void gltf_parse(const void* ptr, uint64_t num_bytes) {
    cgltf_options options = { 0 };
    cgltf_data* data = 0;
    const cgltf_result result = cgltf_parse(&options, ptr, num_bytes, &data);
    if (result == cgltf_result_success) {
        gltf_parse_buffers(data);
        gltf_parse_images(data);
        cgltf_free(data);
    }
}

// parse GLTF buffers and buffer views
static void gltf_parse_buffers(const cgltf_data* gltf) {
    if (gltf->buffer_views_count > SCENE_MAX_BUFFERS) {
        state.failed = true;
        return;
    }

    // parse the buffer-view attributes
    state.scene.num_buffers = gltf->buffer_views_count;
    for (int i = 0; i < state.scene.num_buffers; i++) {
        const cgltf_buffer_view* gltf_buf_view = &gltf->buffer_views[i];
        buffer_t* scene_buffer = &state.scene.buffers[i];
        scene_buffer->gltf_buffer_index = gltf_buf_view->buffer - gltf->buffers;
        scene_buffer->offset = gltf_buf_view->offset;
        scene_buffer->size = gltf_buf_view->size;
        if (gltf_buf_view->type == cgltf_buffer_view_type_indices) {
            scene_buffer->type = SG_BUFFERTYPE_INDEXBUFFER;
        }
        else {
            scene_buffer->type = SG_BUFFERTYPE_VERTEXBUFFER;
        }
        scene_buffer->buffer = sg_alloc_buffer();
    }

    // start loading all buffers
    for (cgltf_size i = 0; i < gltf->buffers_count; i++) {
        const cgltf_buffer* gltf_buf = &gltf->buffers[i];
        gltf_buffer_fetch_userdata_t user_data = {
            .buffer_index = i
        };
        sfetch_send(&(sfetch_request_t){
            .channel = 0,
            .path = gltf_buf->uri,
            .callback = gltf_buffer_fetch_callback,
            .user_data_ptr = &user_data,
            .user_data_size = sizeof(user_data)
        });
    }
}

// parse all the image-related stuff in the GLTF data

// https://github.com/KhronosGroup/glTF/tree/master/specification/2.0#samplerminfilter
static sg_filter gltf_to_sg_filter(int gltf_filter) {
    switch (gltf_filter) {
        case 9728: return SG_FILTER_NEAREST;
        case 9729: return SG_FILTER_LINEAR;
        case 9984: return SG_FILTER_NEAREST_MIPMAP_NEAREST;
        case 9985: return SG_FILTER_LINEAR_MIPMAP_NEAREST;
        case 9986: return SG_FILTER_NEAREST_MIPMAP_LINEAR;
        case 9987: return SG_FILTER_LINEAR_MIPMAP_LINEAR;
        default: return SG_FILTER_LINEAR;
    }
}

// https://github.com/KhronosGroup/glTF/tree/master/specification/2.0#samplerwraps
static sg_wrap gltf_to_sg_wrap(int gltf_wrap) {
    switch (gltf_wrap) {
        case 33071: return SG_WRAP_CLAMP_TO_EDGE;
        case 33648: return SG_WRAP_MIRRORED_REPEAT;
        case 10497: return SG_WRAP_REPEAT;
        default: return SG_WRAP_REPEAT;
    }
}

static void gltf_parse_images(const cgltf_data* gltf) {
    if (gltf->textures_count > SCENE_MAX_IMAGES) {
        state.failed = true;
        return;
    }

    // parse the texture and sampler attributes
    state.scene.num_images = gltf->textures_count;
    for (int i = 0; i < state.scene.num_images; i++) {
        const cgltf_texture* gltf_tex = &gltf->textures[i];
        image_t* scene_image = &state.scene.images[i];
        scene_image->gltf_image_index = gltf_tex->image - gltf->images;
        scene_image->min_filter = gltf_to_sg_filter(gltf_tex->sampler->min_filter);
        scene_image->mag_filter = gltf_to_sg_filter(gltf_tex->sampler->mag_filter);
        scene_image->wrap_s = gltf_to_sg_wrap(gltf_tex->sampler->wrap_s);
        scene_image->wrap_t = gltf_to_sg_wrap(gltf_tex->sampler->wrap_t);
        scene_image->image = sg_alloc_image();
    }

    // start loading all images
    for (cgltf_size i = 0; i < gltf->images_count; i++) {
        const cgltf_image* gltf_img = &gltf->images[i];
        gltf_image_fetch_userdata_t user_data = {
            .image_index = i
        };
        sfetch_send(&(sfetch_request_t){
            .channel = 1,
            .path = gltf_img->uri,
            .callback = gltf_image_fetch_callback,
            .user_data_ptr = &user_data,
            .user_data_size = sizeof(user_data)
        });
    }
}

// create the sokol-gfx buffer objects associated with a GLTF buffer view
static void create_sgbuffers_for_gltfbuffer(int gltf_buffer_index, const uint8_t* bytes, int num_bytes) {
    for (int i = 0; i < state.scene.num_buffers; i++) {
        buffer_t* scene_buffer = &state.scene.buffers[i];
        if (scene_buffer->gltf_buffer_index == gltf_buffer_index) {
            assert((scene_buffer->offset + scene_buffer->size) <= num_bytes);
            sg_init_buffer(scene_buffer->buffer, &(sg_buffer_desc){
                .size = scene_buffer->size,
                .type = scene_buffer->type,
                .content = bytes + scene_buffer->offset
            });
        }
    }
}

// create the sokol-gfx image objects associated with a GLTF image
static void create_sgimages_for_gltfimage(int gltf_image_index, const uint8_t* bytes, int num_bytes) {
    for (int i = 0; i < state.scene.num_images; i++) {
        image_t* scene_image = &state.scene.images[i];
        if (scene_image->gltf_image_index == gltf_image_index) {
            // assume this is an image which can be decoded by stb_image.h
            int img_width, img_height, num_channels;
            const int desired_channels = 4;
            stbi_uc* pixels = stbi_load_from_memory(
                bytes, num_bytes,
                &img_width, &img_height,
                &num_channels, desired_channels);
            if (pixels) {
                /* ok, time to actually initialize the sokol-gfx texture */
                sg_init_image(scene_image->image, &(sg_image_desc){
                    .width = img_width,
                    .height = img_height,
                    .pixel_format = SG_PIXELFORMAT_RGBA8,
                    .min_filter = scene_image->min_filter,
                    .mag_filter = scene_image->mag_filter,
                    .content.subimage[0][0] = {
                        .ptr = pixels,
                        .size = img_width * img_height * 4,
                    }
                });
                stbi_image_free(pixels);
            }
        }
    }
}

sapp_desc sokol_main(int argc, char* argv[]) {
    return (sapp_desc){
        .init_cb = init,
        .frame_cb = frame,
        .cleanup_cb = cleanup,
        .event_cb = __dbgui_event,
        .width = 800,
        .height = 600,
        .sample_count = SAMPLE_COUNT,
        .gl_force_gles2 = true,
        .window_title = "GLTF Viewer",
    };
}



