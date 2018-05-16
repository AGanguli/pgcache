#if !defined (_Global_h_)
#define _Global_h_

namespace SmartCache
{
namespace Global
{

	enum class PauseMode	{ NONE, SUSPEND, PAUSE };
	void 			pauseMode(PauseMode new_mode);
	PauseMode 		pauseMode();

	enum class ShutdownMode	{ NONE = 0, WAITING = 1, IMMEDIATE = 2};
	void			shutdownMode(ShutdownMode new_mode);
	ShutdownMode		shutdownMode();

	void			rebootMode(bool new_mode);
	bool			rebootMode();

	
}

} // namespace SmartCache

#endif
