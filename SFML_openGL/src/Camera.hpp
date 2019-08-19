#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
	using vec3 = glm::vec3;
	using mat4 = glm::mat4;
public:
	vec3 Position;
	vec3 WorldUp;
	
	vec3 Forward;
	vec3 Right;
	vec3 Up;
	
	
public:
	Camera(vec3 position_, vec3 target_, vec3 world_up_)
		: Position(position_)
		, WorldUp(world_up_)
		, Forward(glm::normalize(target_ - position_))
		, Right(glm::normalize(glm::cross(Forward, WorldUp)))
		, Up(glm::normalize(glm::cross(Forward, Right)))
	{
	}

	Camera(vec3 position_, float pitch_, float yaw_, vec3 world_up_)
		: Position(position_)
		, WorldUp(world_up_)
		, Forward(vec3{
			glm::cos(pitch_) * glm::sin(yaw_),
			glm::sin(pitch_),
			glm::cos(pitch_) * glm::cos(yaw_)})
		, Right(glm::normalize(glm::cross(Forward, WorldUp)))
		, Up(glm::normalize(glm::cross(Forward, Right)))
	{
	}

	auto getViewMatrix() -> mat4
	{
		return glm::lookAt(Position, Position + Forward, WorldUp);
	}

private:
	
};
