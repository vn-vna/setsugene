#include <setsugen/engine.h>
#include <setsugen/scripting.h>

class MoveBehavior : public setsugen::Behavior
{
public:
  MoveBehavior(setsugen::Entity* entity) : setsugen::Behavior{entity}
  {}

  void update() override
  {
    auto transform = get_entity()->get_component<setsugen::Transform>();
    if (transform)
    {
      auto rotation = transform->get_rotation();
      transform->set_rotation({rotation.x() + 0.01f, rotation.y(), rotation.z()});
    }
  }

  const char* get_type() override
  {
    return "MoveBehavior";
  }
};

int
main()
{
  using namespace setsugen;
  auto application = ApplicationBuilder::create()->build();
  auto logger      = application->create_logger("main");

  application->run();

  logger->info("Application started");

  logger->info("Creating scene");
  auto scene_manager = application->get_scene_manager();

  auto scene = scene_manager->create_scene("MAIN");

  auto entity        = scene->create_entity("Root");
  auto entity_camera = scene->create_entity("Camera");
  auto dummy         = scene->create_entity("Dummy");

  auto mesh      = entity->add_component<Mesh>("/user/mesh/untitled.fbx");
  auto transform = entity->add_component<Transform>();
  transform->set_position({3.0f, 0.0f, 0.0f});

  auto dummy_mesh      = dummy->add_component<Mesh>("/user/mesh/untitled.fbx");
  auto dummy_behavior  = dummy->add_component<MoveBehavior>();
  auto dummy_transform = dummy->add_component<Transform>();
  dummy_transform->set_position({1.0f, 1.5f, 0.0f});

  const auto camera = entity_camera->add_component<PerspectiveCamera>();
  camera->set_position({0.0f, 2.0f, -5.0f});
  camera->set_center({0.0f, 0.0f, 0.0f});

  auto fbsize = application->get_window()->get_framebuffer_size();
  camera->set_aspect_ratio((float) fbsize.width() / (float) fbsize.height());

  scene->set_main_camera(camera);

  scene_manager->set_current_scene(scene);

  logger->info("Scene created");

  logger->info("Hold on to your butts!");
  application->join();
}
