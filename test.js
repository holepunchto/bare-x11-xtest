const test = require('brittle')
const { Display, constants, stringToKeysym } = require('bare-x11')
const xtest = require('.')

const { BUTTON1_MASK, SHIFT_MASK } = constants

function open(t) {
  const display = Display.open()

  t.teardown(() => display.close())

  return display
}

test('the server has XTEST', (t) => {
  const display = open(t)

  const version = xtest.queryExtension(display)

  t.ok(version !== null && version.major >= 2)
})

test('moves the pointer', (t) => {
  const display = open(t)

  xtest.fakeMotionEvent(display, xtest.CURRENT_SCREEN, 12, 34)
  display.sync()

  const { rootX, rootY } = display.queryPointer(display.defaultRootWindow)

  t.alike({ rootX, rootY }, { rootX: 12, rootY: 34 })
})

test('presses and releases a button', (t) => {
  const display = open(t)
  const root = display.defaultRootWindow

  xtest.fakeButtonEvent(display, 1, true)
  display.sync()

  t.ok(display.queryPointer(root).mask & BUTTON1_MASK, 'pressed')

  xtest.fakeButtonEvent(display, 1, false)
  display.sync()

  t.absent(display.queryPointer(root).mask & BUTTON1_MASK, 'released')
})

test('presses and releases a key', (t) => {
  const display = open(t)
  const root = display.defaultRootWindow

  const keycode = display.keysymToKeycode(stringToKeysym('Shift_L'))

  xtest.fakeKeyEvent(display, keycode, true)
  display.sync()

  t.ok(display.queryPointer(root).mask & SHIFT_MASK, 'pressed')

  xtest.fakeKeyEvent(display, keycode, false)
  display.sync()

  t.absent(display.queryPointer(root).mask & SHIFT_MASK, 'released')
})

test('takes only a display', (t) => {
  t.exception.all(() => xtest.queryExtension({}), /Expected a display/)
})

test('cannot use a closed display', (t) => {
  const display = Display.open()

  display.close()

  t.exception(() => xtest.fakeButtonEvent(display, 1, true), /Display is closed/)
})
