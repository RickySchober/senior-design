#include "StateMachine.h"

void StateMachine::HandleInput(Msg::StateMachineInput input) {
    switch (state_)
    {
    /////////////////////////////////////////////////////////////////////////
    // STANDBY /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    case state::STANDBY:
        if (input.type == Msg::StateMachineInput::MANUAL) {
            state_ = state::MANUAL;
        }
        else if (input.type == Msg::StateMachineInput::START) {
            state_ = state::WAYPOINT;
        }
        else if (input.type == Msg::StateMachineInput::NEW_WAYPOINT) {
            AddWaypoint(input.new_waypoint);
        }
    break;
    /////////////////////////////////////////////////////////////////////////
    // WAYPOINT /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    case state::WAYPOINT:
        if (input.type == Msg::StateMachineInput::NEW_WAYPOINT) {
            AddWaypoint(input.new_waypoint);
        }
    break;

    default:
        break;
    }
}


state::State StateMachine::DecideState() {
    switch (state_)
    {
    /////////////////////////////////////////////////////////////////////////
    // STANDBY /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    case state::STANDBY:
    break;

    /////////////////////////////////////////////////////////////////////////
    // WAYPOINT /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    case state::WAYPOINT:
        if (AllWaypointsDone()) {
            state_ = state::RETURN;
        }
        else if (AtTheWaypoint()) {
            state_ = state::PROFILING;
        }
        else if (IsVehicleInDanger()) {
            state_ = state::RETURN;
        }
    break;
    /////////////////////////////////////////////////////////////////////////
    // PROFILING ////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    case state::PROFILING:
        if (IsProfileDone()) {
            PopWaypoint();
            state_ = state::WAYPOINT;
        }
    break;
    /////////////////////////////////////////////////////////////////////////
    // RETURN ///////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    case state::RETURN:
        if (AtTheWaypoint()) {
            state_ = state::STANDBY;
        }
    break;
    default:
    break;
    }
}

state::State StateMachine::ExecuteState() {
    switch (state_)
    {
    case state::STANDBY:
        // (1) save home coordinates
        // (2) display command menu
        //      (2.1) print out collected data
        //      (2.2) print out health of all systems
        home_coordinates_ = UpdateCurrentLocation();
    break;
    /////////////////////////////////////////////////////////////////////////
    // WAYPOINT /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    case state::WAYPOINT:
        auto current_waypoint = GetCurrentWaypoint();
        UpdateCurrentLocation();
        GotoWaypoint(current_waypoint);
    break;
    /////////////////////////////////////////////////////////////////////////
    // PROFILING ////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    case state::PROFILING:
        //gotodepth()
    break;
    /////////////////////////////////////////////////////////////////////////
    // RETURN ///////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    case state::RETURN:
        UpdateCurrentLocation();
        GotoWaypoint(home_coordinates_);
        break;
    default:
        break;
    }
}

void StateMachine::Input(Msg::StateMachineInput input) {
    if (input.type == Msg::StateMachineInput::NEW_WAYPOINT) {
        AddWaypoint(input.new_waypoint);
    }
}