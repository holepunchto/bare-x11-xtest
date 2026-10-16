#include <assert.h>
#include <bare.h>
#include <js.h>
#include <stdbool.h>
#include <stdint.h>

#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>

#include "x11.h"

static js_value_t *
bare_x11_xtest_query_extension(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1);

  Display *display;
  if (bare_x11_read_display(env, argv[0], &display) < 0) return NULL;

  int event_base, error_base, major, minor;

  js_value_t *result;

  if (!XTestQueryExtension(display, &event_base, &error_base, &major, &minor)) {
    err = js_get_null(env, &result);
    assert(err == 0);

    return result;
  }

  err = js_create_object(env, &result);
  assert(err == 0);

  js_value_t *val;

  err = js_create_int32(env, major, &val);
  assert(err == 0);

  err = js_set_named_property(env, result, "major", val);
  assert(err == 0);

  err = js_create_int32(env, minor, &val);
  assert(err == 0);

  err = js_set_named_property(env, result, "minor", val);
  assert(err == 0);

  return result;
}

static js_value_t *
bare_x11_xtest_fake_motion_event(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 5;
  js_value_t *argv[5];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 5);

  Display *display;
  if (bare_x11_read_display(env, argv[0], &display) < 0) return NULL;

  int32_t screen;
  err = js_get_value_int32(env, argv[1], &screen);
  assert(err == 0);

  int32_t x;
  err = js_get_value_int32(env, argv[2], &x);
  assert(err == 0);

  int32_t y;
  err = js_get_value_int32(env, argv[3], &y);
  assert(err == 0);

  uint32_t delay;
  err = js_get_value_uint32(env, argv[4], &delay);
  assert(err == 0);

  XTestFakeMotionEvent(display, screen, x, y, delay);

  return NULL;
}

static js_value_t *
bare_x11_xtest__fake(js_env_t *env, js_callback_info_t *info, int (*fake)(Display *, unsigned int, Bool, unsigned long)) {
  int err;

  size_t argc = 4;
  js_value_t *argv[4];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 4);

  Display *display;
  if (bare_x11_read_display(env, argv[0], &display) < 0) return NULL;

  uint32_t code;
  err = js_get_value_uint32(env, argv[1], &code);
  assert(err == 0);

  bool press;
  err = js_get_value_bool(env, argv[2], &press);
  assert(err == 0);

  uint32_t delay;
  err = js_get_value_uint32(env, argv[3], &delay);
  assert(err == 0);

  fake(display, code, press, delay);

  return NULL;
}

static js_value_t *
bare_x11_xtest_fake_button_event(js_env_t *env, js_callback_info_t *info) {
  return bare_x11_xtest__fake(env, info, XTestFakeButtonEvent);
}

static js_value_t *
bare_x11_xtest_fake_key_event(js_env_t *env, js_callback_info_t *info) {
  return bare_x11_xtest__fake(env, info, XTestFakeKeyEvent);
}

static js_value_t *
bare_x11_xtest_exports(js_env_t *env, js_value_t *exports) {
  int err;

#define V(name, fn) \
  { \
    js_value_t *val; \
    err = js_create_function(env, name, -1, fn, NULL, &val); \
    assert(err == 0); \
    err = js_set_named_property(env, exports, name, val); \
    assert(err == 0); \
  }

  V("queryExtension", bare_x11_xtest_query_extension)
  V("fakeMotionEvent", bare_x11_xtest_fake_motion_event)
  V("fakeButtonEvent", bare_x11_xtest_fake_button_event)
  V("fakeKeyEvent", bare_x11_xtest_fake_key_event)
#undef V

  return exports;
}

BARE_MODULE(bare_x11_xtest, bare_x11_xtest_exports)
