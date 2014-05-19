#include <pebble.h>

static Window *window;
static TextLayer *hello_layer;


static void window_load(Window *window) {
  char *texty = "the dmv is a horrible service and i'm not sure why c cannot connect to api's more easily";
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  hello_layer = text_layer_create((GRect) { .origin = { 0, 0 }, .size = { 144, 168 } });
  text_layer_set_text(hello_layer, texty);
  text_layer_set_text_alignment(hello_layer, GTextAlignmentLeft);
  text_layer_set_overflow_mode(hello_layer, GTextOverflowModeWordWrap);
  layer_add_child(window_layer, text_layer_get_layer(hello_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(hello_layer);
}

static void init(void) {
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });

  const bool animated = true;
  window_stack_push(window, animated);
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed watchface helloworld: %p", window);

  app_event_loop();
  deinit();
}