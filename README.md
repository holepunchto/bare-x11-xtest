# bare-x11-xtest

XTest bindings for Bare. XTest is the X11 extension that lets a client fake input: the server treats the events as if they came from a real mouse or keyboard, so the app under test handles them the way it handles a person. Use it in tests, such as under `Xvfb`, which supports XTest.

```
npm i -D bare-x11-xtest
```

## Usage

```js
const { Display } = require('bare-x11')
const xtest = require('bare-x11-xtest')

const display = Display.open()

xtest.fakeMotionEvent(display, xtest.CURRENT_SCREEN, 100, 200)
xtest.fakeButtonEvent(display, 1, true)
xtest.fakeButtonEvent(display, 1, false)

display.sync()
```

## License

Apache-2.0
