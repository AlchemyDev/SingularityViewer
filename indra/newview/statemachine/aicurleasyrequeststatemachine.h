/**
 * @file aicurleasyrequest.h
 * @brief Perform a curl easy request.
 *
 * Copyright (c) 2012, Aleric Inglewood.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * There are special exceptions to the terms and conditions of the GPL as
 * it is applied to this Source Code. View the full text of the exception
 * in the file doc/FLOSS-exception.txt in this software distribution.
 *
 * CHANGELOG
 *   and additional copyright holders.
 *
 *   06/05/2012
 *   Initial version, written by Aleric Inglewood @ SL
 */

#ifndef AICURLEASYREQUEST_H
#define AICURLEASYREQUEST_H

#include "aistatemachine.h"
#include "aicurl.h"

// A curl easy request state machine.
//
// Before calling cersm.run() initialize the object (cersm) as follows:
//
// AICurlEasyRequest_wat cersm_w(cersm);
// cersm_w->setopt(...); // etc, see the interface of AICurlPrivate::CurlEasyRequest and it's base class AICurlPrivate::CurlEasyHandle.
//
// When the state machine finishes, call aborted() to check
// whether or not the statemachine succeeded in fetching
// the URL or not.
//
// Objects of this type can be reused multiple times, see
// also the documentation of AIStateMachine.
//
// Construction of a AICurlEasyRequestStateMachine might throw AICurlNoEasyHandle.
class AICurlEasyRequestStateMachine : public AIStateMachine, public AICurlEasyHandleEvents {
  public:
	AICurlEasyRequestStateMachine(bool buffered);

	// Transparent access.
	AICurlEasyRequest mCurlEasyRequest;

  private:
	bool mBuffered;		// Argument used for construction of mCurlEasyRequest.

  protected:
	// AICurlEasyRequest Events.

	// Called when this curl easy handle was added to a multi handle.
	/*virtual*/ void added_to_multi_handle(AICurlEasyRequest_wat&);

	// Called when this curl easy handle finished processing (right before it is removed from the multi handle).
	/*virtual*/ void finished(AICurlEasyRequest_wat&);

	// Called after this curl easy handle was removed from a multi handle.
	/*virtual*/ void removed_from_multi_handle(AICurlEasyRequest_wat&);

  protected:
	// AIStateMachine implementations.

	// Call finish() (or abort()), not delete.
	/*virtual*/ ~AICurlEasyRequestStateMachine();

	// Handle initializing the object.
	/*virtual*/ void initialize_impl(void);

	// Handle mRunState.
	/*virtual*/ void multiplex_impl(void);

	// Handle aborting from current bs_run state.
	/*virtual*/ void abort_impl(void);

	// Handle cleaning up from initialization (or post abort) state.
	/*virtual*/ void finish_impl(void);

	// Implemenation of state_str for run states.
	/*virtual*/ char const* state_str_impl(state_type run_state) const;
};

#endif
