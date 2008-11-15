/*
 *
 *
 * Copyright  1990-2008 Sun Microsystems, Inc. All Rights Reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version
 * 2 only, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License version 2 for more details (a copy is
 * included at /legal/license.txt).
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with this work; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 * Please contact Sun Microsystems, Inc., 4150 Network Circle, Santa
 * Clara, CA 95054 or visit www.sun.com if you need additional
 * information or have any questions.
 *
 * This source file is specific for Qt-based configurations.
 */

#include <lfjport_export.h>
#include <japplication.h>
#include <jdisplay.h>
#include "lfjport_qtopia_screen.h"
#include <midp_logging.h>
#include <midp_constants_data.h>

/**
 * @file
 * Additional porting API for Java Widgets based port of abstract
 * command manager.
 */

int lfjport_ui_init_cpp()
{
  JApplication::init();
  JDisplay::init();
  LFJScreen::init();
  JDisplay::current()->addWidget(LFJScreen::instance());
  JDisplay::current()->setCurrentWidget(LFJScreen::instance());
  //#error Add LFJScreen initialization here!
  JApplication *app = JApplication::instance();
  app->showMainWidget(JDisplay::current());
  return 0;
}

void lfjport_ui_finalize_cpp()
{
  JDisplay::current()->hide();
  JDisplay::destroy();
  JApplication::destroy();
}

void lfjport_refresh_cpp(int x1, int y1, int x2, int y2)
{
  JDisplay::current()->update(x1, y1, x2-x1+1, y2-y1+1);
}

int lfjport_set_vertical_scroll_cpp(int scrollPosition, int scrollProportion)
{
  /* Suppress unused parameter warnings */
  (void)scrollPosition;
  (void)scrollProportion;
    //!TODO
#warning Think about lfjport_set_vertical_scroll
  return 0;
}

void lfjport_set_fullscreen_mode_cpp(jboolean mode)
{
  JDisplay::current()->setFullScreenMode(mode);
}

jboolean lfjport_reverse_orientation_cpp()
{
  JDisplay::current()->setReversedOrientation(!JDisplay::current()->reversedOrientation());
  return JDisplay::current()->reversedOrientation();
}

jboolean lfjport_get_reverse_orientation_cpp()
{
  return JDisplay::current()->reversedOrientation();
}

int lfjport_get_screen_width_cpp()
{
  return JDisplay::current()->displayWidth();
}

int lfjport_get_screen_height_cpp()
{
  return JDisplay::current()->displayHeight();
}

jboolean lfjport_is_fullscreen_mode_cpp()
{
  return JDisplay::current()->fullScreenMode();
}

void lfjport_gained_foreground_cpp()
{

}

jboolean lfjport_direct_flush_cpp(const java_graphics *g, const java_imagedata *offscreen_buffer, int h)
{
  (void)g; (void)offscreen_buffer; (void)h;

  return KNI_FALSE;
}

jboolean lfjport_is_native_softbutton_layer_supported_cpp()
{
  return KNI_TRUE;
}

void lfjport_set_softbutton_label_on_native_layer_cpp(unsigned short *label, int len, int index)
{
  QString qstr_label = QString::fromUtf16(label, len);
  LFJScreen::instance()->setSoftButtonLabel(index, qstr_label);
}

extern "C"
{
  /**
  * Initializes the LCDUI native resources.
  *
  * @return <tt>0</tt> upon successful initialization, or
  *         <tt>other value</tt> otherwise
  */
  int lfjport_ui_init()
  {
    return lfjport_ui_init_cpp();
  }

  /**
  * Finalize the LCDUI native resources.
  */
  void lfjport_ui_finalize()
  {
    lfjport_ui_finalize_cpp();
  }

  /**
  * Bridge function to request a repaint
  * of the area specified.
  *
  * @param x1 top-left x coordinate of the area to refresh
  * @param y1 top-left y coordinate of the area to refresh
  * @param x2 bottom-right x coordinate of the area to refresh
  * @param y2 bottom-right y coordinate of the area to refresh
  */
  void lfjport_refresh(int x1, int y1, int x2, int y2)
  {
    lfjport_refresh_cpp(x1, y1, x2, y2);
  }

  /**
  * Porting API function to update scroll bar.
  *
  * @param scrollPosition current scroll position
  * @param scrollProportion maximum scroll position
  * @return status of this call
  */
  int lfjport_set_vertical_scroll(int scrollPosition, int scrollProportion)
  {
    return lfjport_set_vertical_scroll_cpp(scrollPosition, scrollProportion);
  }

  /**
  * Turn on or off the full screen mode
  *
  * @param mode true for full screen mode
  *             false for normal
  */
  void lfjport_set_fullscreen_mode(jboolean mode)
  {
    lfjport_set_fullscreen_mode_cpp(mode);
  }

  jboolean lfjport_reverse_orientation()
  {
    return lfjport_reverse_orientation_cpp();
  }

  jboolean lfjport_get_reverse_orientation()
  {
    return lfjport_get_reverse_orientation_cpp();
  }

  int lfjport_get_screen_width()
  {
    return lfjport_get_screen_width_cpp();
  }

  int lfjport_get_screen_height()
  {
    return lfjport_get_screen_height_cpp();
  }

  /**
  * Bridge function to ask MainWindow object for the full screen mode
  * status.
  */
  jboolean lfjport_is_fullscreen_mode()
  {
    return lfjport_is_fullscreen_mode_cpp();
  }

  /**
  * Resets native resources when foreground is gained by a new display.
  */
  void lfjport_gained_foreground()
  {
    lfjport_gained_foreground_cpp();
  }

  /**
  * Flushes the offscreen buffer directly to the device screen.
  * The size of the buffer flushed is defined by offscreen buffer width
  * and passed in height.
  * Offscreen_buffer must be aligned to the top-left of the screen and
  * its width must be the same as the device screen width.
  * @param graphics The Graphics handle associated with the screen.
  * @param offscreen_buffer The ImageData handle associated with
  *                         the offscreen buffer to be flushed
  * @param height The height to be flushed
  * @return KNI_TRUE if direct_flush was successful, KNI_FALSE - otherwise
  */
  jboolean lfjport_direct_flush(const java_graphics *g,
                    const java_imagedata *offscreen_buffer, int h)
  {
    return lfjport_direct_flush_cpp(g, offscreen_buffer, h);
  }

  /**
  * Check if native softbutton is supported on platform
  *
  * @return KNI_TRUE if native softbutton is supported, KNI_FALSE - otherwise
  */
  jboolean lfjport_is_native_softbutton_layer_supported()
  {
    return lfjport_is_native_softbutton_layer_supported_cpp();
  }

  /**
  * Request platform to draw a label in the soft button layer.
  *
  * @param label Label to draw (UTF16)
  * @param len Length of the lable (0 will cause removal of current label)
  * @param index Index of the soft button in the soft button bar.
  */
  void lfjport_set_softbutton_label_on_native_layer (unsigned short *label, int len, int index)
  {
    lfjport_set_softbutton_label_on_native_layer_cpp(label, len, index);
  }
}
