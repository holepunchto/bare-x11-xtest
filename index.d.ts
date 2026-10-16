import { Display } from 'bare-x11'

/** The screen the pointer is on, for `fakeMotionEvent()`. */
export const CURRENT_SCREEN: -1

/** `XTestQueryExtension()`: the version of XTEST, or `null` if the server lacks it. */
export function queryExtension(display: Display): { major: number; minor: number } | null

/**
 * `XTestFakeMotionEvent()`: move the pointer to a point on the root window of `screen`, after
 * `delay` milliseconds.
 */
export function fakeMotionEvent(
  display: Display,
  screen: number,
  x: number,
  y: number,
  delay?: number
): void

/** `XTestFakeButtonEvent()`: press or release button 1 to 5, after `delay` milliseconds. */
export function fakeButtonEvent(
  display: Display,
  button: number,
  press: boolean,
  delay?: number
): void

/** `XTestFakeKeyEvent()`: press or release the key with `keycode`, after `delay` milliseconds. */
export function fakeKeyEvent(
  display: Display,
  keycode: number,
  press: boolean,
  delay?: number
): void
