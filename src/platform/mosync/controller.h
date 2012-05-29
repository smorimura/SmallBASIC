// This file is part of SmallBASIC
//
// Copyright(C) 2001-2012 Chris Warren-Smith.
//
// This program is distributed under the terms of the GPL v2.0 or later
// Download the GNU Public License (GPL) from www.gnu.org
//

#include <MAUtil/Environment.h>
#include <MAUtil/String.h>

#include "config.h"
#include "common/sbapp.h"
#include "common/sys.h"
#include "common/smbas.h"
#include "common/osd.h"
#include "common/device.h"
#include "common/blib_ui.h"

#include "platform/mosync/ansiwidget.h"

using namespace MAUtil;

struct Controller : public Environment {
  Controller();
  virtual ~Controller();

  enum ExecState {
    init_state,
    run_state,
    restart_state,
    modal_state,
    break_state,
    conn_state,
    exit_state
  };

  void modalLoop();
  void pause(int ms);
  MAEvent processEvents(int ms, int untilType);
  char *readConnection(const char *url);

  bool isExit() { return runMode == exit_state; }
  bool isModal() { return runMode == modal_state; }
  bool isRun() { return runMode == run_state; }
  void setRunning() { runMode = run_state; }

  AnsiWidget *output;

private:
  ExecState runMode;
};
