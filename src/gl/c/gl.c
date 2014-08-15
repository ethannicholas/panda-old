#include "SDL.h"
#include "SDL_image.h"
#include "dlfcn.h"
#include "cairo.h"
// FIXME rename pandalib.h to panda.h
#include "pandalib.h"
#include "gl.h"

// -------- Initialization, Windows, and Surfaces --------

void pandaGLInit() {
    static Bit initialized = false;
    if (!initialized) {
        SDL_Init(SDL_INIT_VIDEO);
        panda$gl$events$EventType$$classInit();
        panda$gl$events$Key$$classInit();
        initialized = true;
    }
}

panda$gl$events$Event* pandaCreateEvent(SDL_Event* event);

void panda$gl$GLMessageQueue$pumpEvents(panda$gl$GLMessageQueue* self) {
    panda$threads$MessageQueue$post_TYPE* post =
            (panda$threads$MessageQueue$post_TYPE*) 
                *(&self->cl->vtable + panda$threads$MessageQueue$post_INDEX);    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        post((panda$threads$MessageQueue*) self, 
                (panda$core$Immutable*) pandaCreateEvent(&event));
    }
}

void panda$gl$GLMessageQueue$waitForEvent(panda$gl$GLMessageQueue* self) {
    panda$threads$MessageQueue$hasMessage_TYPE* hasMessage =
            (panda$threads$MessageQueue$hasMessage_TYPE*) 
                *(&self->cl->vtable + panda$threads$MessageQueue$hasMessage_INDEX);    
    if (!hasMessage((panda$threads$MessageQueue*) self)) {
        panda$threads$MessageQueue$post_TYPE* post =
                (panda$threads$MessageQueue$post_TYPE*) 
                    *(&self->cl->vtable + panda$threads$MessageQueue$post_INDEX);    
        SDL_Event event;
        SDL_WaitEvent(&event);
        post((panda$threads$MessageQueue*) self, 
                (panda$core$Immutable*) pandaCreateEvent(&event));
    }
}

void panda$gl$GLMessageQueue$waitForEvent_Int32(panda$gl$GLMessageQueue* self,
        int timeout) {
    panda$gl$GLMessageQueue$waitForEvent(self);
}

void panda$gl$Window$init(panda$gl$Window* self, String* title, Int32 x, 
        Int32 y, Int32 width, Int32 height) {
    pandaGLInit();
    self->native = SDL_CreateWindow(pandaGetString(title), x, y, width, 
            height, 0);
}

typedef struct NativeRenderer {
    SDL_Surface* windowSurface;
    SDL_Surface* sdlSurface;
    cairo_surface_t* cairoSurface;
    cairo_t* context;
    SDL_Window* window;
} NativeRenderer;

panda$gl$Renderer* panda$gl$Window$createRenderer(panda$gl$Window* window) {
    panda$gl$Renderer* result = pandaNew(panda$gl$Renderer);
    panda$gl$Renderer$new(result);

    NativeRenderer* renderer = MALLOC(sizeof(NativeRenderer));
    SDL_Surface* sdlSurface = SDL_CreateRGBSurface(
            0, 
            window->bounds->width, 
            window->bounds->height, 
            32,
            0x00FF0000, /* Rmask */
            0x0000FF00, /* Gmask */
            0x000000FF, /* Bmask */
            0); /* Amask */
    renderer->sdlSurface = sdlSurface;
    cairo_surface_t* cairoSurface = cairo_image_surface_create_for_data(
        sdlSurface->pixels,
        CAIRO_FORMAT_RGB24,
        sdlSurface->w,
        sdlSurface->h,
        sdlSurface->pitch);
    renderer->cairoSurface = cairoSurface;
    renderer->windowSurface = SDL_GetWindowSurface(
            (SDL_Window*) window->native);

    cairo_t* context = cairo_create(cairoSurface);
    renderer->context = context;
    renderer->window = window->native;

    cairo_select_font_face(context, "sans-serif", CAIRO_FONT_SLANT_NORMAL, 
            CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(context, 12.0);
    cairo_set_source_rgb(context, 1.0, 1.0, 1.0);

    result->native = renderer;

    return result;
}

void panda$gl$Window$close(panda$gl$Window* window) {
    SDL_DestroyWindow(window->native);
}

void panda$gl$Renderer$close(panda$gl$Renderer* renderer) {
    SDL_DestroyRenderer(renderer->native);
}

void panda$gl$Texture$close(panda$gl$Texture* texture) {
    SDL_DestroyTexture(texture->native);
}


// -------- Drawing --------

void panda$gl$Renderer$_save(panda$gl$Renderer* renderer) {
    cairo_t* context = ((NativeRenderer*) renderer->native)->context;
    cairo_save(context);
}

void panda$gl$Renderer$_restore(panda$gl$Renderer* renderer) {
    cairo_t* context = ((NativeRenderer*) renderer->native)->context;
    cairo_restore(context);
}

void panda$gl$Renderer$setPaint(panda$gl$Renderer* renderer,
        panda$gl$Paint* paint) {
    cairo_t* context = ((NativeRenderer*) renderer->native)->context;
    panda$gl$Color* color = (panda$gl$Color*) paint;
    cairo_set_source_rgb(context, color->red, color->green, color->blue);
}

void panda$gl$Renderer$setTransform(panda$gl$Renderer* renderer,
        panda$gl$Transform* transform) {
    cairo_matrix_t matrix;
    cairo_matrix_init(&matrix, transform->m00, transform->m10, transform->m01,
            transform->m11, transform->m02, transform->m12);
    cairo_t* context = ((NativeRenderer*) renderer->native)->context;
    cairo_set_matrix(context, &matrix);
}

void pandaCreatePath(panda$gl$Renderer* renderer, 
        panda$gl$shapes$Shape* shape) {
    cairo_t* context = ((NativeRenderer*) renderer->native)->context;
    panda$gl$shapes$Shape$path_TYPE* getPath =
            (panda$gl$shapes$Shape$path_TYPE*) pandaGetInterfaceMethod(
                (panda$core$Object*) shape,
                &panda$gl$shapes$Shape_class, 
                panda$gl$shapes$Shape$path_INDEX);
    panda$gl$Transform$transform_TYPE* transform;
    panda$gl$shapes$PathSegment$Array* path = getPath(shape);
    int i;
    for (i = 0; i < path->$length; i++) {
        panda$gl$shapes$PathSegment* segment = path->contents[i];
        double x = segment->position->x;
        double y = segment->position->y;
        switch (segment->type->value) {
            case 0 /* MOVE */:
                cairo_move_to(context, x, y);
                break;
            case 1 /* LINE */:
                cairo_line_to(context, x, y);
                break;
            case 2 /* CURVE */: {
                panda$gl$shapes$PathSegmentCurve* curve = 
                        (panda$gl$shapes$PathSegmentCurve*) segment;
                cairo_curve_to(context, 
                        curve->controlPoint1->x, 
                        curve->controlPoint1->y, 
                        curve->controlPoint2->x, 
                        curve->controlPoint2->y, 
                        x, 
                        y);
                break;
            }
        }
    }

}

void panda$gl$Renderer$clip(panda$gl$Renderer* renderer,
        panda$gl$shapes$Shape* clip) {
    cairo_t* context = ((NativeRenderer*) renderer->native)->context;
    pandaCreatePath(renderer, clip);
    cairo_clip(context);
}

void panda$gl$Renderer$resetClip(panda$gl$Renderer* renderer) {
    cairo_t* context = ((NativeRenderer*) renderer->native)->context;
    cairo_reset_clip(context);
}

void panda$gl$Renderer$fill(panda$gl$Renderer* renderer, 
        panda$gl$shapes$Shape* shape) {
    pandaCreatePath(renderer, shape);
    cairo_t* context = ((NativeRenderer*) renderer->native)->context;
    cairo_fill(context);
}

void panda$gl$Renderer$stroke(panda$gl$Renderer* renderer, 
        panda$gl$shapes$Shape* shape) {
    pandaCreatePath(renderer, shape);
    cairo_t* context = ((NativeRenderer*) renderer->native)->context;
    cairo_stroke(context);
}

void panda$gl$Renderer$clear(panda$gl$Renderer* renderer) {
    cairo_t* context = ((NativeRenderer*) renderer->native)->context;
    panda$gl$Color* color = (panda$gl$Color*) renderer->_paint;
    cairo_set_source_rgb(context, color->red, color->green, color->blue);
    cairo_paint(context);
}

void panda$gl$Renderer$present(panda$gl$Renderer* renderer) {
    NativeRenderer* native = (NativeRenderer*) renderer->native;
    SDL_BlitSurface(native->sdlSurface, NULL, native->windowSurface, NULL);
    SDL_UpdateWindowSurface(native->window);
}


// -------- Images --------

void pandaPremultiply(UInt8* pixels, int pitch, int width, int height) {
    int x;
    int y;
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            float alpha = pixels[x * 4 + 3] / 255.0;
            pixels[x * 4] *= alpha;
            pixels[x * 4 + 1] *= alpha;
            pixels[x * 4 + 2] *= alpha;
        }
        pixels += pitch;
    }
}

panda$gl$images$Image* panda$gl$images$Image$load(panda$io$File* file) {
    SDL_Surface* sdlSurface = IMG_Load(pandaGetString(file->path));
    panda$gl$images$Image* result = pandaNew(panda$gl$images$Image);
    printf("assuming ARGB32 image for now - premultiplying\n");
    pandaPremultiply(sdlSurface->pixels, sdlSurface->pitch, sdlSurface->w,
            sdlSurface->h);
    cairo_surface_t* cairoSurface = cairo_image_surface_create_for_data(
            sdlSurface->pixels,
            CAIRO_FORMAT_ARGB32,
            sdlSurface->w,
            sdlSurface->h,
            sdlSurface->pitch);
    result->native = cairoSurface;
    result->_width = sdlSurface->w;
    result->_height = sdlSurface->h;
    return result;
}

void panda$gl$Renderer$drawImage(panda$gl$Renderer* renderer, 
            panda$gl$images$Image* image, panda$gl$shapes$Rectangle* dest) {
    cairo_t* context = ((NativeRenderer*) renderer->native)->context;
    if (dest->width != image->_width || dest->height != image->_height) {
        cairo_save(context);
        cairo_translate(context, dest->x, dest->y);
        cairo_scale(context, dest->width / image->_width,
                dest->height / image->_height);
        cairo_set_source_surface(context, (cairo_surface_t*) image->native, 
                0, 0);
        cairo_paint(context);
        cairo_restore(context);
    }
    else {
        cairo_set_source_surface(context, (cairo_surface_t*) image->native, 
                dest->x, dest->y);
        cairo_paint(context);
    }
}

void panda$gl$images$Image$close(panda$gl$images$Image* image) {
    cairo_surface_destroy((cairo_surface_t*) image->native);
}

// -------- Event Handling --------

void pandaInitializeKeyEvent(panda$gl$events$KeyEvent* result, 
        SDL_KeyboardEvent* event) {
    switch (event->keysym.sym) {
        case SDLK_a:
            result->key = class_panda$gl$events$Key$A; 
            break;
        case SDLK_b:
            result->key = class_panda$gl$events$Key$B;
            break;
        case SDLK_c:
            result->key = class_panda$gl$events$Key$C;
            break;
        case SDLK_d:
            result->key = class_panda$gl$events$Key$D;
            break;
        case SDLK_e:
            result->key = class_panda$gl$events$Key$E;
            break;
        case SDLK_f:
            result->key = class_panda$gl$events$Key$F;
            break;
        case SDLK_g:
            result->key = class_panda$gl$events$Key$G;
            break;
        case SDLK_h:
            result->key = class_panda$gl$events$Key$H;
            break;
        case SDLK_i:
            result->key = class_panda$gl$events$Key$I;
            break;
        case SDLK_j:
            result->key = class_panda$gl$events$Key$J;
            break;
        case SDLK_k:
            result->key = class_panda$gl$events$Key$K;
            break;
        case SDLK_l:
            result->key = class_panda$gl$events$Key$L;
            break;
        case SDLK_o:
            result->key = class_panda$gl$events$Key$O;
            break;
        case SDLK_p:
            result->key = class_panda$gl$events$Key$P;
            break;
        case SDLK_q:
            result->key = class_panda$gl$events$Key$Q;
            break;
        case SDLK_r:
            result->key = class_panda$gl$events$Key$R;
            break;
        case SDLK_s:
            result->key = class_panda$gl$events$Key$S;
            break;
        case SDLK_t:
            result->key = class_panda$gl$events$Key$T;
            break;
        case SDLK_u:
            result->key = class_panda$gl$events$Key$U;
            break;
        case SDLK_v:
            result->key = class_panda$gl$events$Key$V;
            break;
        case SDLK_w:
            result->key = class_panda$gl$events$Key$W;
            break;
        case SDLK_x:
            result->key = class_panda$gl$events$Key$X;
            break;
        case SDLK_y:
            result->key = class_panda$gl$events$Key$Y;
            break;
        case SDLK_z:
            result->key = class_panda$gl$events$Key$Z;
            break;
        case SDLK_LEFTBRACKET:
            result->key = class_panda$gl$events$Key$LEFT_BRACKET;
            break;
        case SDLK_RIGHTBRACKET:
            result->key = class_panda$gl$events$Key$RIGHT_BRACKET;
            break;
        case SDLK_BACKSPACE: 
            result->key = class_panda$gl$events$Key$BACKSPACE; 
            break;
        case SDLK_TAB: 
            result->key = class_panda$gl$events$Key$TAB; 
            break;
        case SDLK_LEFT: 
            result->key = class_panda$gl$events$Key$LEFT; 
            break;
        case SDLK_RIGHT: 
            result->key = class_panda$gl$events$Key$RIGHT; 
            break;
        case SDLK_UP: 
            result->key = class_panda$gl$events$Key$UP; 
            break;
        case SDLK_DOWN: 
            result->key = class_panda$gl$events$Key$DOWN; 
            break;
        case SDLK_SPACE: 
            result->key = class_panda$gl$events$Key$SPACE; 
            break;
        case SDLK_ESCAPE: 
            result->key = class_panda$gl$events$Key$ESCAPE; 
            break;
        case SDLK_LSHIFT:
            result->key = class_panda$gl$events$Key$LEFT_SHIFT;
            break;
        case SDLK_RSHIFT:
            result->key = class_panda$gl$events$Key$RIGHT_SHIFT;
            break;
        default: 
            result->key = class_panda$gl$events$Key$UNKNOWN; 
    }
    result->modifiers = event->keysym.mod;
}

void pandaInitializeMouseEvent(panda$gl$events$MouseEvent* result,
        SDL_MouseButtonEvent* event) {
    result->button = event->button;
    panda$gl$Point* position = pandaNew(panda$gl$Point);
    position->x = event->x;
    position->y = event->y;
    result->position = position;
}

void pandaInitializeMouseMotionEvent(panda$gl$events$MouseMotionEvent* result,
        SDL_MouseMotionEvent* event) {
    panda$gl$Point* position = pandaNew(panda$gl$Point);
    position->x = event->x;
    position->y = event->y;
    result->position = position;
}

panda$gl$events$Event* pandaCreateEvent(SDL_Event* event) {
    switch (event->type) {
        case SDL_KEYDOWN: {
            panda$gl$events$KeyEvent* result = pandaNew(
                    panda$gl$events$KeyEvent);
            SDL_KeyboardEvent* keyEvent = (SDL_KeyboardEvent*) event;
            result->type = keyEvent->repeat ? 
                class_panda$gl$events$EventType$KEYREPEAT : 
                class_panda$gl$events$EventType$KEYDOWN;
            pandaInitializeKeyEvent(result, keyEvent);
            return (panda$gl$events$Event*) result;
        }
        case SDL_KEYUP: {
            panda$gl$events$KeyEvent* result = pandaNew(
                    panda$gl$events$KeyEvent);
            result->type = class_panda$gl$events$EventType$KEYUP;
            pandaInitializeKeyEvent(result, (SDL_KeyboardEvent*) event);
            return (panda$gl$events$Event*) result;
        }
        case SDL_MOUSEMOTION: {
            panda$gl$events$MouseMotionEvent* result = pandaNew(
                    panda$gl$events$MouseMotionEvent);
            result->type = class_panda$gl$events$EventType$MOUSEMOTION;
            pandaInitializeMouseMotionEvent(result, 
                    (SDL_MouseMotionEvent*) event);
            return (panda$gl$events$Event*) result;
        }
        case SDL_MOUSEBUTTONDOWN: {
            panda$gl$events$MouseEvent* result = pandaNew(
                    panda$gl$events$MouseEvent);
            result->type = class_panda$gl$events$EventType$MOUSEDOWN;
            pandaInitializeMouseEvent(result, 
                    (SDL_MouseButtonEvent*) event);
            return (panda$gl$events$Event*) result;
        }
        case SDL_MOUSEBUTTONUP: {
            panda$gl$events$MouseEvent* result = pandaNew(
                    panda$gl$events$MouseEvent);
            result->type = class_panda$gl$events$EventType$MOUSEUP;
            pandaInitializeMouseEvent(result, 
                    (SDL_MouseButtonEvent*) event);
            return (panda$gl$events$Event*) result;
        }
        default: {
            panda$gl$events$Event* result = pandaNew(
                    panda$gl$events$Event);
            result->type = class_panda$gl$events$EventType$UNKNOWN;
            return result;
        };
    }
}

void panda$gl$Window$startRenderLoop(panda$gl$Window* self, void** m) {
    panda$gl$Renderer$present_TYPE* present =
            (panda$gl$Renderer$present_TYPE*) 
                *(&self->renderer->cl->vtable + 
                    panda$gl$Renderer$present_INDEX);    
    panda$gl$Renderer$save_TYPE* save =
            (panda$gl$Renderer$save_TYPE*) 
                *(&self->renderer->cl->vtable + 
                    panda$gl$Renderer$save_INDEX);    
    panda$gl$Renderer$restore_TYPE* restore =
            (panda$gl$Renderer$restore_TYPE*) 
                *(&self->renderer->cl->vtable + 
                    panda$gl$Renderer$restore_INDEX);    
    Real64 target = 1000.0 / 60.0;
    Real64 totalTicks = SDL_GetTicks() - target;
    Real64 frameTicks = target;
    for (;;) {
        save(self->renderer);
        ((void(*)(void*,Real64)) *(&((panda$core$Method*) m)->cl->vtable + 
                panda$core$Method$$CNVpanda$core$MutableMethod_INDEX + 1))(m, frameTicks);
        restore(self->renderer);
        present(self->renderer);
        Real64 newTicks = SDL_GetTicks();
        frameTicks = newTicks - totalTicks;
        if (frameTicks < target) {
            SDL_Delay(target - frameTicks);
            newTicks = SDL_GetTicks();
            frameTicks = newTicks - totalTicks;
        }
        totalTicks = newTicks;
    }
}
