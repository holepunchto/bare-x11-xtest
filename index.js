const binding = require('./binding')

const handle = Symbol.for('bare.x11.display')

exports.CURRENT_SCREEN = -1

exports.queryExtension = function queryExtension(display) {
  return binding.queryExtension(display[handle])
}

exports.fakeMotionEvent = function fakeMotionEvent(display, screen, x, y, delay = 0) {
  binding.fakeMotionEvent(display[handle], screen, x, y, delay)
}

exports.fakeButtonEvent = function fakeButtonEvent(display, button, press, delay = 0) {
  binding.fakeButtonEvent(display[handle], button, press, delay)
}

exports.fakeKeyEvent = function fakeKeyEvent(display, keycode, press, delay = 0) {
  binding.fakeKeyEvent(display[handle], keycode, press, delay)
}
