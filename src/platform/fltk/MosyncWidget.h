// This file is part of SmallBASIC
//
// Copyright(C) 2001-2013 Chris Warren-Smith.
//
// This program is distributed under the terms of the GPL v2.0 or later
// Download the GNU Public License (GPL) from www.gnu.org
// 

#ifndef MOSYNC_WIDGET
#define MOSYNC_WIDGET

#include <fltk/Widget.h>
#include <fltk/Image.h>
#include <fltk/draw.h>

#include "platform/mosync/interface.h"

struct AnsiWidget;

struct Canvas {
  Canvas(int size);
  ~Canvas();

  void beginDraw();
  void clear();
  void create(int w, int h);
  void draw(int w, int h);
  void endDraw();
  void resize(int w, int h);
  void setClip(int x, int y, int w, int h);
  void setFont();

  fltk::Image *_img;
  fltk::Rectangle *_clip;
  int _rgb;
  int _size;
  int _style;
};

class MosyncWidget : public fltk::Widget, IButtonListener {
public:
  MosyncWidget(int x, int y, int w, int h, int defsize);
  virtual ~MosyncWidget();

  void clearScreen();
  void print(const char *str);
  void drawLine(int x1, int y1, int x2, int y2);
  void drawRectFilled(int x1, int y1, int x2, int y2);
  void drawRect(int x1, int y1, int x2, int y2);
  void drawImage(fltk::Image *img, int x, int y, int sx, int sy, int w, int h);
  void saveImage(const char *fn, int x, int y, int w, int h);
  void setTextColor(long fg, long bg);
  void setColor(long color);
  int  getX();
  int  getY();
  void setPixel(int x, int y, int c);
  int  getPixel(int x, int y);
  void setXY(int x, int y);
  int  textHeight(void);
  void setFontSize(float i);
  int  getFontSize();
  int  getBackgroundColor();
  void flush(bool force);
  void reset();

  Canvas *getScreen() { return _screen; }
  int getDefaultSize() { return _defsize; }

private:
  // inherited methods
  void draw();
  void layout();
  int handle(int e);

  void buttonClicked(const char *action);
  AnsiWidget *_ansiWidget;
  Canvas *_screen;
  bool _resized;
  int _defsize;
};

#endif