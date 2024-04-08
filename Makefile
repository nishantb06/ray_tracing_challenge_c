tests:
	gcc ray_tracer/tests/test_tuple.c -o ray_tracer/bin/test_tuple
	gcc ray_tracer/tests/test_canvas.c -o ray_tracer/bin/test_canvas
	gcc ray_tracer/tests/test_matrix.c -o ray_tracer/bin/test_matrix
	gcc ray_tracer/tests/test_transformation.c -o ray_tracer/bin/test_transformation
	gcc ray_tracer/tests/test_ray.c -o ray_tracer/bin/test_ray
	gcc ray_tracer/tests/test_light.c -o ray_tracer/bin/test_light  

run_tests:
	./ray_tracer/bin/test_tuple
	./ray_tracer/bin/test_canvas
	./ray_tracer/bin/test_matrix
	./ray_tracer/bin/test_transformation
	./ray_tracer/bin/test_ray
	./ray_tracer/bin/test_light

plot_sphere:
	gcc ray_tracer/plot_sphere.c -o ray_tracer/bin/plot_sphere && ./ray_tracer/bin/plot_sphere 

test_scene:
	gcc ray_tracer/tests/test_scene.c -o ray_tracer/bin/test_scene && ray_tracer/bin/test_scene

plot_spheres_ch8:
	gcc ray_tracer/plot_spheres.c -o ray_tracer/bin/plot_spheres && ray_tracer/bin/plot_spheres && open plot_spheres.ppm