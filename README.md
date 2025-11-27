# Cub3D
A first-person raycasting engine inspired by Wolfenstein 3D, developed in C using the MiniLibX graphical library.<br>
The player can explore a 3D environment rendered from a 2D map, navigate around walls, through doors and rotate the camera in real time.

## Installation
```
git clone
cd Cub3D
```
- For version without mini-map and animated sprite
```
cd mandatory
make all
```
-For version with mini-map and animated sprite
```
cd bonus
make all
```

## Usage
```
./cub3D map/map_simple.cub
```

## Controls
**W**: Move forward <br>
**S**: Move backward <br>
**A**: Move left <br>
**D**: Move right <br>
**Touchpad / mouse**: Rotate camera <br>
**ESC**: Quit the game

## Dev features
- Robust map parsing and validation
- Custom raycasting engine
- Real-time 3D rendering based on a 2D map
- Smooth player movement and camera rotation
- Mini-map to guide player movement
- Animated sprite
- Descriptive error handling

## Tecnical notes
- Raycasting calculates the distance from the player to the closest wall for each rendered column (projected wall slice).<br>
  **The Digital Differential Analyzer (DDA)** algorithm is used to detect wall intersections by advancing the ray through the grid cell by cell and checking horizontal and vertical crossings until a wall is hit.
<img width="567" height="523" alt="check-horizontal-intersection" src="https://github.com/user-attachments/assets/0910a7d1-571b-4fdf-8c0f-7b186ecd3dd8" />
<img width="540" height="351" alt="check-vertical-intersection" src="https://github.com/user-attachments/assets/e1cc4467-40ed-42a2-b702-aacd50d7af54" /> <br>

- Wall scaling illustration
<img width="832" height="712" alt="Wall-scaling-illustration" src="https://github.com/user-attachments/assets/45216b87-b7d5-4d82-bcc5-43c2749e0e46" /><br>

- Mouse movement updates the camera by tracking the latest and previous cursor positions.Each mouse movement creates a new node holding the latest cursor coordinates at the head of a linked list. The next node has the previous cursor coordinates. Two cursor coordinates are then compared to detect horizontal or vertical motion of player's view, which leads to update of the frame. A drawback of this approach is that it can produce memory leaks if the linked list grows unchecked.

## Demo
![Cub4D](https://github.com/user-attachments/assets/578db84c-7c0b-48bc-8fcc-78a61cfc01db)
