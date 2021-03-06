#ifndef STATE_MANAGER_HPP
#define STATE_MANAGER_HPP

#include "Common.h"
#include "Helpers.hpp"
#include "InputManager.hpp"

class AbstractState;
class StateManager
{
public:
	StateManager(sf::String window_title, int window_width, int window_height);
	~StateManager();

	int getregionWidth(){ return width; }
	int getregionHeight() { return height; }
	void setregionWidth(int rw){ width = rw; }
	void setregionHeight(int rh){ height = rh; }



	void change_state(std::unique_ptr<AbstractState> state);
	void push_state(std::unique_ptr<AbstractState> state);
	void pop_state();

	int run();

	void quit()
	{
		running_ = false;
	}

	sf::RenderWindow& get_render_window()
	{
		return render_window_;
	}

	InputManager& get_input_manager()
	{
		return input_manager_;
	}

	template<typename T>
	std::unique_ptr<T> state_ptr();

	template<typename T>
	std::unique_ptr<T> state_ptr(bool load);

	void setPoints(int p) { points = p; }
	int getPoints() { return points; }
protected:
private:
	sf::RenderWindow render_window_;
	InputManager input_manager_;

	std::stack<std::unique_ptr<AbstractState>> states_;

	bool running_;

	const sf::Time time_per_frame_;
	int width;
	int height;
	void render();
	void update(const sf::Time& delta);
	void handle_input(const sf::Time& delta);
	void handle_state_changes();
	int points;
	bool is_running() const { return running_ && render_window_.isOpen(); }
};

template<typename T>
std::unique_ptr<T> StateManager::state_ptr()
{
	return std::move(std::unique_ptr<T>(new T(*this)));
}

template<typename T>
std::unique_ptr<T> StateManager::state_ptr(bool load_from_file)
{
	return std::move(std::unique_ptr<T>(new T(*this, load_from_file)));
}

#endif