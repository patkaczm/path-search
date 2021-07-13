import QtQuick 2.12

Item {
    id: rectangleThickMazePainter
    property var currentMaze: undefined;
    function reset(ctx) {
        ctx.reset()
    }
    function drawMaze(maze, ctx) {
        console.log("hello")
        currentMaze = maze;
        let newGridSizeWidth = (gridSizeWidth.value * 2) + 1
        let newGridSizeHeight = (gridSizeHeight.value * 2) + 1
        let cellXSize = width / newGridSizeWidth;
        let cellYSize = height / newGridSizeHeight;

        ctx.reset()

        ctx.beginPath();
        ctx.fillStyle="black";
        ctx.fillRect(0, 0, width, height);
        ctx.fill();


        ctx.beginPath();
        ctx.fillStyle = "white";
        for (var i = 0; i < maze.length; i++) {
            let x = ( 2 *(i % gridSizeWidth.value) + 1)* cellXSize;
            let y = (2 * Math.floor(i / gridSizeWidth.value) + 1)* cellYSize

            ctx.fillRect(x, y, cellXSize , cellYSize );
            if (gridView.isSet(maze[i], 0)) {
                ctx.fillRect(x + cellXSize, y, cellXSize, cellYSize);
            }
            if (gridView.isSet(maze[i], 1)) {
                ctx.fillRect(x, y + cellYSize, cellXSize, cellYSize);
            }
        }
        ctx.fill();
    }
}
