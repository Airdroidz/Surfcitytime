#include <pebble.h>

static Window *s_main_window;
static BitmapLayer *s_background_layer;
static GBitmap *s_background_bitmap;
static TextLayer *s_time_layer;
static TextLayer *s_date_layer;

// State variable to track if the colon should be visible this second
static bool s_colon_visible = true;

static void update_time() {
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  // 1. Format the Time (12h/24h style) with blinking colon
  static char s_time_buffer[8];
  if (clock_is_24h_style()) {
    strftime(s_time_buffer, sizeof(s_time_buffer), s_colon_visible ? "%H:%M" : "%H %M", tick_time);
  } else {
    strftime(s_time_buffer, sizeof(s_time_buffer), s_colon_visible ? "%I:%M" : "%I %M", tick_time);
  }
  
  char *time_ptr = s_time_buffer;
  if (!clock_is_24h_style() && s_time_buffer[0] == '0') {
    time_ptr = &s_time_buffer[1];
  }
  text_layer_set_text(s_time_layer, time_ptr);

  // 2. Format the Date (e.g., "Jul 06")
  static char s_date_buffer[12];
  strftime(s_date_buffer, sizeof(s_date_buffer), "%b %d", tick_time);
  text_layer_set_text(s_date_layer, s_date_buffer);
}

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // 1. Setup Surf City Background Image
  s_background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BACKGROUND);
  if (s_background_bitmap != NULL) {
    s_background_layer = bitmap_layer_create(bounds);
    bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap);
    layer_add_child(window_layer, bitmap_layer_get_layer(s_background_layer));
  }

  // Sky Banner Region Settings
  int banner_x = 30; 
  int banner_width = 84;

  // 2. Setup the Time Layer
  s_time_layer = text_layer_create(GRect(banner_x, 15, banner_width, 24));
  text_layer_set_background_color(s_time_layer, GColorClear); 
  text_layer_set_text_color(s_time_layer, GColorBlack); 
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(s_time_layer));

  // 3. Setup the Date Layer
  s_date_layer = text_layer_create(GRect(banner_x, 36, banner_width, 16));
  text_layer_set_background_color(s_date_layer, GColorClear);
  text_layer_set_text_color(s_date_layer, GColorDarkGray);
  text_layer_set_font(s_date_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD));
  text_layer_set_text_alignment(s_date_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(s_date_layer));

  update_time();
}

static void main_window_unload(Window *window) {
  text_layer_destroy(s_date_layer);
  text_layer_destroy(s_time_layer);
  if (s_background_layer) {
    bitmap_layer_destroy(s_background_layer);
  }
  if (s_background_bitmap) {
    gbitmap_destroy(s_background_bitmap);
  }
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  s_colon_visible = !s_colon_visible;
  update_time();
}

static void init() {
  s_main_window = window_create();
  window_set_background_color(s_main_window, GColorVividCerulean);

  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  window_stack_push(s_main_window, true);

  tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
}

static void deinit() {
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}