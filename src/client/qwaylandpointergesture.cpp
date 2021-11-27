#include "qwaylandpointergesture_p.h"
#include "qwaylandinputdevice_p.h"
#include "qwaylanddisplay_p.h"
#include "qwaylandsurface_p.h"
#include "qwaylandwindow_p.h"

QT_BEGIN_NAMESPACE

namespace QtWaylandClient {

Q_LOGGING_CATEGORY(lcQpaWaylandPointerGesture, "qt.qpa.wayland.pointergesture", QtWarningMsg);

QWaylandPointerGesture::QWaylandPointerGesture(QWaylandDisplay *display, uint32_t id, uint32_t version)
    : QtWayland::zwp_pointer_gestures_v1(display->wl_registry(), id, version),
      mDisplay(display)
{
    qCDebug(lcQpaWaylandPointerGesture) << Q_FUNC_INFO << id;
}

QWaylandPointerSwipeGesture::QWaylandPointerSwipeGesture(QWaylandDisplay *display, QTouchDevice *touchDevice, struct ::zwp_pointer_gesture_swipe_v1 *object)
    : QtWayland::zwp_pointer_gesture_swipe_v1(object),
      mDisplay(display),
      mTouchDevice(touchDevice)
{
    qCDebug(lcQpaWaylandPointerGesture) << Q_FUNC_INFO << mDisplay << mTouchDevice;
}

void QWaylandPointerSwipeGesture::zwp_pointer_gesture_swipe_v1_begin(uint32_t serial, uint32_t time, struct ::wl_surface *surface, uint32_t fingers)
{
      qCDebug(lcQpaWaylandPointerGesture) << Q_FUNC_INFO << serial << time << fingers;

//    auto *window = QWaylandWindow::fromWlSurface(surface);
//    if (!window) {
//        return;
//    }
//    mWindow = window;

//    QPointF localPos = mDisplay->defaultInputDevice()->pointerSurfacePosition();
//    QPointF globalPos = mWindow->mapToGlobal(localPos.toPoint());
//    QWindowSystemInterface::handleGestureEvent(mWindow->window(), mTouchDevice, time, Qt::BeginNativeGesture, localPos, globalPos);
}

void QWaylandPointerSwipeGesture::zwp_pointer_gesture_swipe_v1_update(uint32_t time, wl_fixed_t dx, wl_fixed_t dy)
{
    qCDebug(lcQpaWaylandPointerGesture) << Q_FUNC_INFO << time << dx << dy;
//    QPointF localPos = mDisplay->defaultInputDevice()->pointerSurfacePosition();
//    QPointF globalPos = mWindow->mapToGlobal(localPos.toPoint());
//    QWindowSystemInterface::handleGestureEvent(mWindow->window(), mTouchDevice, time, Qt::SwipeNativeGesture, localPos, globalPos);
}

void QWaylandPointerSwipeGesture::zwp_pointer_gesture_swipe_v1_end(uint32_t serial, uint32_t time, int32_t cancelled)   
{
    qCDebug(lcQpaWaylandPointerGesture) << Q_FUNC_INFO << serial << time << cancelled;
//    QPointF localPos = mDisplay->defaultInputDevice()->pointerSurfacePosition();
//    QPointF globalPos = mWindow->mapToGlobal(localPos.toPoint());
//    QWindowSystemInterface::handleGestureEvent(mWindow->window(), mTouchDevice, time, Qt::EndNativeGesture, localPos, globalPos);
}

QWaylandPointerPinchGesture::QWaylandPointerPinchGesture(QWaylandDisplay *display, QTouchDevice *touchDevice, struct ::zwp_pointer_gesture_pinch_v1 *object)
    : QtWayland::zwp_pointer_gesture_pinch_v1(object),
      mDisplay(display),
      mTouchDevice(touchDevice)
{
    qCDebug(lcQpaWaylandPointerGesture) << Q_FUNC_INFO << mDisplay << mTouchDevice;
}

void QWaylandPointerPinchGesture::zwp_pointer_gesture_pinch_v1_begin(uint32_t serial, uint32_t time, struct ::wl_surface *surface, uint32_t fingers)
{
    qCDebug(lcQpaWaylandPointerGesture) << Q_FUNC_INFO << serial << time << fingers;

    auto *window = QWaylandWindow::fromWlSurface(surface);
    if (!window) {
        return;
    }
    mWindow = window;

    QPointF localPos = mDisplay->defaultInputDevice()->pointerSurfacePosition();
    QPointF globalPos = mWindow->mapToGlobal(localPos.toPoint());
    QWindowSystemInterface::handleGestureEvent(mWindow->window(), mTouchDevice, time, Qt::BeginNativeGesture, localPos, globalPos);
}

void QWaylandPointerPinchGesture::zwp_pointer_gesture_pinch_v1_update(uint32_t time, wl_fixed_t dx, wl_fixed_t dy, wl_fixed_t scale, wl_fixed_t rotation)
{
    qCDebug(lcQpaWaylandPointerGesture) << Q_FUNC_INFO << time << dx << dy << scale << rotation;
    QPointF localPos = mDisplay->defaultInputDevice()->pointerSurfacePosition();
    QPointF globalPos = mWindow->mapToGlobal(localPos.toPoint());

    QWindowSystemInterface::handleGestureEventWithRealValue(mWindow->window(), mTouchDevice, time,
                                                            Qt::ZoomNativeGesture, wl_fixed_to_double(scale),
                                                            localPos, globalPos);

    QWindowSystemInterface::handleGestureEventWithRealValue(mWindow->window(), mTouchDevice, time,
                                                            Qt::RotateNativeGesture, wl_fixed_to_double(rotation),
                                                            localPos, globalPos);
}

void QWaylandPointerPinchGesture::zwp_pointer_gesture_pinch_v1_end(uint32_t serial, uint32_t time, int32_t cancelled)
{
    qCDebug(lcQpaWaylandPointerGesture) << Q_FUNC_INFO << serial << time << cancelled;

    QPointF localPos = mDisplay->defaultInputDevice()->pointerSurfacePosition();
    QPointF globalPos = mWindow->mapToGlobal(localPos.toPoint());
    QWindowSystemInterface::handleGestureEvent(mWindow->window(), mTouchDevice, time, Qt::EndNativeGesture, localPos, globalPos);
}

}
QT_END_NAMESPACE
