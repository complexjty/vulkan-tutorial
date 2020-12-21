project('vulkan', 'c', 'cpp', default_options: ['c_std=c11', 'cpp_std=c++2a', 'warning_level=2', 'werror=false'])

glfw_dep = dependency('glfw3')
vulkan_dep = dependency('vulkan')

src = [
       'src/main.cxx',
       'src/vk_app.cxx',
       'src/glfw_window.cxx',
       'src/vk_instance.cxx',
      ]

cc  = meson.get_compiler('c')
ccx = meson.get_compiler('cpp')

executable('vulkan-tutorial', sources: src, dependencies: [vulkan_dep, glfw_dep])

