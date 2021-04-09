
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>



//ECS
#include "SingleIncludes/ecs.h"

//Context Var
#include "ContextTypes/WindowDetails.h"
#include "ContextTypes/Camera.h"
#include "ContextTypes/InputState.h"

//Helpers
#include "Helpers/TimeKeeper.h"
#include "Helpers/ErrorLogging.h"
#include "Helpers/ManageTerrain.h"
#include "Helpers/Shader.h"
#include "Helpers/MakeCube.h"
#include "Helpers/PathFinding.h"
#include "Helpers/WaveHelpers.h"
#include "Helpers/Logger.h"



//Systems
#include "Systems/RenderingSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/ImGuiRendering.h"
#include "Systems/PlacementSystem.h"
#include "Systems/SpawnSystem.h"
#include "Systems/TravellerSystem.h"
#include "Systems/ThreatTargettingSystem.h"



int main()
{
	//Init registry
	Registry registry{};
	auto& windowDetails = registry.ctx_or_set<WindowDetails>(1600, 900);

	auto errLogger = spdlog::stderr_color_mt("error_logger", spdlog::color_mode::always);
	auto debugLogger = spdlog::stdout_color_mt("debug_logger", spdlog::color_mode::always);
	
	spdlog::set_level(spdlog::level::debug);

	//GLFW init
	if (!glfwInit())
	{
		ERR_LOG("Unable to initialise glfw!");
		return -1;
	}



	//Creating window, may want to make this more flexible.
	GLFWwindow* window = glfwCreateWindow(windowDetails.w, windowDetails.h, "Tower Defence", nullptr, nullptr);
	windowDetails.window = window;
	//Checking window created
	if (!window)
	{
		ERR_LOG("Unable to create glfw window!");
		return -1;
	}
	glfwMakeContextCurrent(window);

	//Init glad
	if (!gladLoadGL())
	{
		ERR_LOG("Unable to initialise GLAD!");
		return -1;
	}



	//ImGui Init
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();


	ImGui_ImplGlfw_InitForOpenGL(windowDetails.window, true);
	ImGui_ImplOpenGL3_Init();


	spdlog::debug("Now initialised OpenGL with version: {0}", glGetString(GL_VERSION));
	spdlog::log(spdlog::level::debug, "Successfully initialised");

	{//For initing basic shapes and models into OpenGL e.g. InitCube()

		InitCube();

	}



	//INIT FUNCTIONS FOR SYSTEMS/HELPERS
	{

		registry.set<std::unordered_map<std::string, void*>>(); //Needed by input system

		Input::InitInputSystem(registry);

		//Terrain
		Terrain::InitTerrain(registry);
		PlaceInit(registry);
		InitPath(registry);
		const glm::vec3 position{ 0.5F * TERRAIN_BOX_WIDTH, TERRAIN_BOX_WIDTH / 2, -0.5f * TERRAIN_BOX_WIDTH };
		Waves::CreateSpawner(registry, position);


		//Special instance where context variable is a helper object
		Shader defaultShader{ "src/Shaders/default.vert", "src/Shaders/default.frag" };
		defaultShader.RegisterMat4("u_MVP");
		registry.set<Shader>(defaultShader);

		//Init Camera for Registry
		//TODO: Initialise these together possibly?
		registry.set<Camera>();
		registry.set<InputStates>();
		registry.set<ImGuiIO*>(&io);
		registry.set<Logger>();


		glfwSetInputMode(windowDetails.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetInputMode(windowDetails.window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	}


	//REFERENCE TRIANGLE, DO NOT DELETE THIS YET

	const float vertices[9] = {
	-0.5f, -0.5f, -5.0f,
	 0.5f, -0.5f, -5.0f,
	 0.0f,  0.5f, -5.0f
	};
	const unsigned int indices[3] =
	{
		0,1,2
	};

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo, ibo;
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 3*3*sizeof(float), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0,  0);
	glEnableVertexAttribArray(0);





	//TODO: Now just polish up a bit of the controls and allowing ImGUI to change speed etc.

	TimeKeeper timer;
	timer.DeltaTimeBase();
	bool& running = windowDetails.running;
	while (!glfwWindowShouldClose(window) && running)
	{
		const float dt = timer.GetDeltaTime(); //MICROSECONDS
		UpdateRendering(registry, dt);
		UpdatePlacer(registry, dt);
		Spawning::UpdateWave(registry, dt);
		Path::UpdateTravellers(registry, dt);
		Enemy::UpdateThreatSystem(registry, dt);
		Input::UpdateInputStates(registry, dt);


		//TODO: Cooldown system can be applied universally so instead 
		//of making the check inside update wave, can instead make it so that the cooldown 
		//system will take care of it.

		//Render Reference Triangle. DO NOT DELETE THIS YET
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);



		//ImGui stuff, separate into a different system probably/helper
		RenderImgui(registry, dt);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

