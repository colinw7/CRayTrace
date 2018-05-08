raytrace::add_plane -p1 [0,0  ,1] -p2 [1,0  ,1] -p3 [1,0.2,2] -color "red" -image "textures/checkerboard3.png" -reflect 0.2
raytrace::add_plane -p1 [0,0.2,2] -p2 [1,0.2,2] -p3 [1,0.8,2] -color "red" -image "textures/checkerboard3.png" -reflect 0.2
raytrace::add_plane -p1 [0,0.8,2] -p2 [1,0.8,2] -p3 [1,1  ,1] -color "red" -image "textures/checkerboard3.png" -reflect 0.2

raytrace::add_sphere -translate [0.5,0.5,1.2] -radius 0.2 -color "white" -reflect 0.5

raytrace::add_light -position [0,0,1] -color "red"
raytrace::add_light -position [1,1,1] -color "green"

raytrace::render
