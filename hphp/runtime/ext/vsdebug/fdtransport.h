/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2017-present Facebook, Inc. (http://www.facebook.com)  |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/

#ifndef incl_HPHP_VSDEBUG_FDTRANSPORT_H_
#define incl_HPHP_VSDEBUG_FDTRANSPORT_H_

#include "hphp/runtime/ext/vsdebug/transport.h"
#include "hphp/runtime/base/req-malloc.h"

namespace HPHP {
namespace VSDEBUG {

// FdTransport transport speaks to the debugger client via a fd stream on a
// known file descriptor.
struct FdTransport : public DebugTransport {
  FdTransport(Debugger* debugger);
  virtual ~FdTransport() {
    if (m_transportFd != nullptr) {
      fclose(m_transportFd);
      m_transportFd = nullptr;
    }
  }

  int connectedClientCount() const override;

private:

  static constexpr int TransportFd = 3;
};

}
}

#endif // incl_HPHP_VSDEBUG_FDTRANSPORT_H_