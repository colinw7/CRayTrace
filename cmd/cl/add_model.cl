raytrace::add_model -filename "models/v3d/InfLoopShip.V3D" -auto_scale -auto_translate

raytrace::add_light -position [0,0,1] -color "red"
raytrace::add_light -position [1,1,1] -color "green"

raytrace::render
