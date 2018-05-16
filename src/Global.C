#include "Global.h"

namespace SmartCache
{
namespace Global
{
	static 		PauseMode pause_mode 			= PauseMode::NONE;
	void 		pauseMode(PauseMode new_mode) 		{ pause_mode = new_mode; }
	PauseMode 	pauseMode() 				{ return pause_mode; }

	static 		ShutdownMode shutdown_mode 		= ShutdownMode::NONE;
	void 		shutdownMode(ShutdownMode new_mode) 	{ shutdown_mode = new_mode; }
	ShutdownMode	shutdownMode() 				{ return shutdown_mode; }
}

} // namespace SmartCach3
