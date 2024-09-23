# Notes of Digital Mind's interactive fog tutorial

## Overview

Create a basic fog material, and using Niagara Particle System to generate particles which take the fog matrial.

### Important Features

- Movement Control
- Automatically calculate the direction of the fog based on the terrain
- Self Shadowing!
- Extinction Color which control how light color scatter through the fog
- Specify objects that can be interacted

### Volume Rendering Tech

- Voxelization
- Ray Marching

### Fog writing methods

- A mesh
- A particle

Note: both of them need a volume matrial in UE

### Interaction Methods

- Field of particle
- Full fluid simulation
- Mask Texture(Render Target)

### Optimization

- Calculate the right size of the volume box
