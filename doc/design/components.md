# Components

Here we list the components and what they do.  This is currently a work in progress.

**TODO:** Expand descriptions, add remaining things to do.  Flesh this out.  Add more components if they make sense.  Try to keep components as self contained as possible.

### [Engine](#Engine)

Combines all the components together into a working product.

### [Platform](#Platform)

Provides platform independence.

### [Math](#Math)

Provides vector, matrix, and other operations.

### [Renderer](#Renderer)

Provides rendering

### [Physics](#Physics)

Handles physics and collision

### [Resources](#Resources)

Resources and resource management

### [Audio](#Audio)

Handle audio

### [HID](#HID)

Human input devices

### [AI](#AI)

Artificial Intelligence, path finding and decision making.

### [Common](#Common)

Common utilities used across multiple modules.

---

## <a id="Engine">Engine</a>

This is the central entry point which combines all the components together into a cohesive product.

### The current status

*We need to expand on each of these. Add more if needed*

- [ ] Engine
    - [ ] Initialization
    - [ ] Running
    - [ ] Shutdown

## <a id="Platform">Platform</a>

Provides platform independence.  Allows for windows, file management, memory management.

### The current status

*Determine what else is needed, if anything, and add*

- [ ] Platform
    - [ ] UI
        - [x] Display Window
            - [x] Window
            - [x] Linux
            - [ ] OSX
    - [ ] File management
        - [ ] Windows
        - [ ] Linux
        - [ ] OSX
    - [ ] Memory Manager
        - [ ] Allocators
            - [ ] Linear
            - [ ] Stack
            - [ ] Pool
            - [ ] Fixed Block
            - [ ] Buddy Blocks
        - [ ] Compaction
    - [ ] Audio Abstraction
    - [ ] HID Abstraction

## <a id="Math">Math</a>

Provides math functionality.  Matrix and Vector operations are supported with and without SIMD support.  Common trigonometric operations are supported along with interpolation.  Quaternions are also supported.

### Current Status

*Determine what else is needed, if anything, and add*

- [ ] Math
    - [ ] Matrix
        - [ ] 4x4
            - [ ] SIMD
            - [x] CPU
            - [ ] Inverse
            - [x] Vector Multiplication
        - [ ] 3x3
            - [ ] SIMD
            - [ ] CPU
            - [ ] Inverse
            - [ ] Vector Multiplication
    - [ ] Vector
        - [ ] Vec2
            - [x] SIMD
            - [x] CPU
            - [x] Dot Product
        - [ ] Vec3
            - [x] SIMD
            - [x] CPU
            - [x] Dot Product
            - [x] Cross Product
        - [ ] Vec4
            - [x] SIMD
            - [x] CPU
            - [x] Dot Product
    - [ ] Quaternions
        - [ ] TBD


## <a id="Renderer">Renderer</a>

This handles the low level rendering.  Will support rendering geometric objects, shading, and common render operations.

### Current Status

*Be more fine grained, add more.*

- [ ] Renderer
    - [ ] OpenGL
        - [ ] Render an object with no shader
        - [ ] Render an object with shader
        - [ ] Render multiple objects
        - [ ] Render with lighting
    - [ ] Renderable Interface (All renderable objects support)
        - [x] Vertices (Get/Count/Format)
        - [x] Indices (Get/Count)
        - [x] Color (Get/Count)
        - [x] Normals (Get/Count)
        - [x] Texture (Get/Count)

## <a id="Physics">Physics</a>

The physics component provides physics simulation along with collision detection.

### Current Status

*Determine what else is needed, if anything, and add*

- [ ] Collision
    - [ ] Bounding Boxes
        - [ ] Sphere
        - [ ] Rectangle
        - [ ] Generic
        - [ ] Hierarchial
    - [ ] Detection
    - [ ] Penetration handling
- [ ] Physics
    - [ ] Linear Interpolation
    - [ ] Quadratic Interpolation
    - [ ] Quadratic Interpolation
    - [ ] Kinematics
    - [ ] Orbiting

## <a id="Resources">Resources</a>

The resource module handles resources using resource management.  Resource managers ensure that a resource is not loaded twice.

### Current Status

*Determine what else is needed, if anything, and add*

- [ ] Resources
    - [ ] Audio
        - [ ] Manager
        - [ ] mp3
        - [ ] wav
    - [ ] Shaders
        - [ ] Manager
        - [ ] Vertex
        - [ ] Fragment
    - [ ] Shader Program
        - [ ] Manager
    - [ ] Geometric Objects
        - [ ] Manager
        - [ ] Internal Format

## <a id="Audio">Audio</a>

The audio component handles audio processing.

### Current Status

*Determine what else is needed, if anything, and add*

- [ ] Audio
    - [ ] Playback

## <a id="HID">HID</a>

The HID (human interface device) module handles HID objects and the common functionality with them such as user input.

### Current Status

*Determine what else is needed, if anything, and add*
*Can we do a generic interface?*

- [ ] HID
    - [ ] Keyboard
    - [ ] Mouse
    - [ ] Controller
    - [ ] Joystick
    - [ ] Microphone (?)

## <a id="AI">AI</a>

The AI module provides common artificial intelligence algorithms such as path finding and decision making.

### Current Status

*Determine what else is needed, if anything, and add*

- [ ] AI
    - [ ] Path finding
        - [ ] A*
        - [ ] BFS
        - [ ] DFS
    - [ ] Decision Making
        - [ ] TBD

## <a id="Common">Common</a>

This has common utilities for all components.

### Current Status

*Determine what else is needed, if anything, and add*

- [ ] Common
    - [x] Command line arguments
    - [x] Configuration
    - [ ] Time Utilities
        - [ ] Time 
        - [ ] Stopwatch
    - [ ] Scheduler
    - [x] Version
    - [ ] Interfaces
        - [x] ToString
        - [x] Serialization


