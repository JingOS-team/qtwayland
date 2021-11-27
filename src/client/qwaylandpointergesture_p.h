#ifndef QWAYLANDPOINTERGESTURE_H
#define QWAYLANDPOINTERGESTURE_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <qpa/qwindowsysteminterface.h>

#include <QtWaylandClient/private/qwayland-pointer-gestures-unstable-v1.h>
#include <QtWaylandClient/qtwaylandclientglobal.h>

QT_BEGIN_NAMESPACE

class QTouchDevice;

namespace QtWaylandClient {

class QWaylandWindow;
class QWaylandDisplay;

class Q_WAYLAND_CLIENT_EXPORT QWaylandPointerGesture : public QtWayland::zwp_pointer_gestures_v1
{
public:
    QWaylandPointerGesture(QWaylandDisplay *display, uint32_t id, uint32_t version);

private:
    QWaylandDisplay *mDisplay = nullptr;
};

class Q_WAYLAND_CLIENT_EXPORT QWaylandPointerSwipeGesture : public QtWayland::zwp_pointer_gesture_swipe_v1
{
public:
    QWaylandPointerSwipeGesture(QWaylandDisplay *display, QTouchDevice *touchDevice, struct ::zwp_pointer_gesture_swipe_v1 *object);

protected:
    virtual void zwp_pointer_gesture_swipe_v1_begin(uint32_t serial, uint32_t time, struct ::wl_surface *surface, uint32_t fingers);
    virtual void zwp_pointer_gesture_swipe_v1_update(uint32_t time, wl_fixed_t dx, wl_fixed_t dy);
    virtual void zwp_pointer_gesture_swipe_v1_end(uint32_t serial, uint32_t time, int32_t cancelled);

private:
    QWaylandDisplay *mDisplay = nullptr;
    QTouchDevice *mTouchDevice = nullptr;
    QWaylandWindow *mWindow = nullptr;
};

class Q_WAYLAND_CLIENT_EXPORT QWaylandPointerPinchGesture : public QtWayland::zwp_pointer_gesture_pinch_v1
{
public:
    QWaylandPointerPinchGesture(QWaylandDisplay *display, QTouchDevice *touchDevice, struct ::zwp_pointer_gesture_pinch_v1 *object);

protected:
    virtual void zwp_pointer_gesture_pinch_v1_begin(uint32_t serial, uint32_t time, struct ::wl_surface *surface, uint32_t fingers);
    virtual void zwp_pointer_gesture_pinch_v1_update(uint32_t time, wl_fixed_t dx, wl_fixed_t dy, wl_fixed_t scale, wl_fixed_t rotation);
    virtual void zwp_pointer_gesture_pinch_v1_end(uint32_t serial, uint32_t time, int32_t cancelled);

private:
    QWaylandDisplay *mDisplay = nullptr;
    QTouchDevice *mTouchDevice = nullptr;
    QWaylandWindow *mWindow = nullptr;
};

}

QT_END_NAMESPACE

#endif // QWAYLANDPOINTERGESTURE_H
