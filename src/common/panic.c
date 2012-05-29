// This file is part of SmallBASIC
//
// System error manager
//
// This program is distributed under the terms of the GPL v2.0 or later
// Download the GNU Public License (GPL) from www.gnu.org
//
// Copyright(C) 2000 Nicholas Christopoulos

#include "common/sys.h"

#if defined(_WinGUI) || defined(_Win32) || defined(__MINGW32__)
#include <windows.h>
#endif

#if defined(_UnixOS)
#include <assert.h>
#endif

#include "common/panic.h"
#include <assert.h>

static char preload_panic_buffer[SB_PANICMSG_SIZE + 1];

/**
 *
 */
void panic(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
#if defined(_PalmOS)
    StrVPrintF(preload_panic_buffer, fmt, ap);
#elif defined(_DOS)
    vsprintf(preload_panic_buffer, fmt, ap);
#else
    vsnprintf(preload_panic_buffer, SB_PANICMSG_SIZE, fmt, ap);
#endif
    va_end(ap);

#if defined(_BCB_W32_IDE)
    bcb_mgrerr("%s", preload_panic_buffer);
#elif defined(_WinGUI) || defined(_Win32)
    MessageBox(NULL, preload_panic_buffer, "SB Panic", MB_OK);
#elif defined (__MINGW32__)
    MessageBox(NULL, preload_panic_buffer, "SB Panic", MB_OK);
    exit(1);
#elif defined(_VTOS)
    MessageBox("FATAL PANIC", preload_panic_buffer, TRUE);
#elif defined(_FRANKLIN_EBM)
    GUI_Alert(ALERT_ERROR, preload_panic_buffer);
#elif defined(_PalmOS)
    ErrDisplay(preload_panic_buffer);
#else
    fprintf(stderr, "\n\nPANIC: %s\a\n\n", preload_panic_buffer);
    fflush(stderr);

    assert(0);
    memmgr_setabort(1);
    exit(1);
#endif
  }

/**
 *
 */
void warning(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
#if defined(_PalmOS)
    StrVPrintF(preload_panic_buffer, fmt, ap);
#else
    vsprintf(preload_panic_buffer, fmt, ap);
#endif
    va_end(ap);

#if defined(_WinGUI) || defined(_Win32)
    MessageBox(NULL, preload_panic_buffer, "SB Warning", MB_OK);
#elif defined(_PalmOS)
    FrmCustomAlert(InfoAlertID, "Warning:", preload_panic_buffer, "");
//      ErrNonFatalDisplay(preload_panic_buffer);
#elif defined(_VTOS)
    MessageBox("WARNING", preload_panic_buffer, FALSE);
#elif defined(_FRANKLIN_EBM)
    GUI_Alert(ALERT_ERROR, preload_panic_buffer);
#else // defined(_UnixOS)
    fprintf(stderr, preload_panic_buffer, 0);
#endif
  }

/**
 *
 */
void debug(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  strcpy(preload_panic_buffer, "DEBUG: ");
#if defined(_PalmOS)
    StrVPrintF(&preload_panic_buffer[7], fmt, ap);
#else
    vsprintf(&preload_panic_buffer[7], fmt, ap);
#endif
    va_end(ap);

#if defined(_WinGUI) || defined(_Win32)
    MessageBox(NULL, preload_panic_buffer, "SB Debug", MB_OK);
#elif defined(_PalmOS)
    SysFatalAlert(preload_panic_buffer);
#elif defined(_VTOS)
    MessageBox("WARNING", preload_panic_buffer, FALSE);
#elif defined(_FRANKLIN_EBM)
    GUI_Alert(ALERT_ERROR, preload_panic_buffer);
#else // defined(_UnixOS)
    fprintf(stderr, preload_panic_buffer, 0);
#endif
  }

/**
 * memory dump
 */
void hex_dump(const unsigned char *block, int size) {
#if defined(_UnixOS) || defined(_DOS)
  int i, j;

  printf("\n---HexDump---\n\t");
  for (i = 0; i < size; i++) {

    printf("%02X ", block[i]);
    if (((i + 1) % 8) == 0 || (i == size - 1)) {
      printf("  ");
      for (j = ((i - 7 <= 0) ? 0 : i - 7); j <= i; j++) {
        if (block[j] < 32)
        printf(".");
        else
        printf("%c", block[j]);
      }
      printf("\n\t");
    }
  }

  printf("\n");
#endif
}