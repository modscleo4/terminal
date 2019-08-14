// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#pragma once

// HEY YOU: When adding ActionArgs types, make sure to add the corresponding
//          *.g.cpp to ActionArgs.cpp!
#include "ActionEventArgs.g.h"
#include "CopyTextArgs.g.h"
#include "NewTabWithProfileArgs.g.h"
#include "SwitchToTabArgs.g.h"
#include "ResizePaneArgs.g.h"
#include "MoveFocusArgs.g.h"

#include "../../cascadia/inc/cppwinrt_utils.h"

// Notes on defining ActionArgs and ActionEventArgs:
// * All properties specific to an action should be defined as in the ActionArgs
//   class.
// * ActionEventArgs should extend from the ActionArgs class, and add an
//   aditional `Handled` property. For EventArgs that require actual args (ex:
//   NewTabWithProfileEventArgs)
// * For ActionEventArgs:
//   - the ctor is internal to the TerminalApp implementation. It uses the
//     implementation type of the IActionArgs. This lets us construct the args
//     without getting the activation factory.
//   - You need to manually set each member of the EventArgs using the Args
//     that's passed in. DO NOT declare the properties a second time in the
//     event! Because the EventArgs class uses the Args class as a base class,
//     the EventArgs already has methods for each property defined.

namespace winrt::TerminalApp::implementation
{
    struct ActionEventArgs : public ActionEventArgsT<ActionEventArgs>
    {
        ActionEventArgs() = default;
        ActionEventArgs(const TerminalApp::IActionArgs& args) :
            _ActionArgs{ args } {};
        GETSET_PROPERTY(IActionArgs, ActionArgs, nullptr);
        GETSET_PROPERTY(bool, Handled, false);
    };

    struct CopyTextArgs : public CopyTextArgsT<CopyTextArgs>
    {
        CopyTextArgs() = default;
        GETSET_PROPERTY(bool, TrimWhitespace, false);
    };

    struct NewTabWithProfileArgs : public NewTabWithProfileArgsT<NewTabWithProfileArgs>
    {
        NewTabWithProfileArgs() = default;
        GETSET_PROPERTY(int32_t, ProfileIndex, 0);
    };

    struct SwitchToTabArgs : public SwitchToTabArgsT<SwitchToTabArgs>
    {
        SwitchToTabArgs() = default;
        GETSET_PROPERTY(int32_t, TabIndex, 0);
    };

    struct ResizePaneArgs : public ResizePaneArgsT<ResizePaneArgs>
    {
        ResizePaneArgs() = default;
        GETSET_PROPERTY(TerminalApp::Direction, Direction, TerminalApp::Direction::Left);
    };

    struct MoveFocusArgs : public MoveFocusArgsT<MoveFocusArgs>
    {
        MoveFocusArgs() = default;
        GETSET_PROPERTY(TerminalApp::Direction, Direction, TerminalApp::Direction::Left);
    };

}

namespace winrt::TerminalApp::factory_implementation
{
    BASIC_FACTORY(ActionEventArgs);
}
