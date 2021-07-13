import QtQuick 2.12

Canvas {
    id: rectangleThinMazePainter
    property var currentMaze: undefined;

    function reset(ctx) {
//        let ctx = rectangleThinMaze.getContext("2d");
        ctx.reset();
    }

    function drawMaze(maze, ctx) {
        currentMaze = maze;
        let cellXSize = width / gridSizeWidth.value;
        let cellYSize = height / gridSizeHeight.value;
        console.log(cellXSize, cellYSize);

//        let ctx = rectangleThinMaze.getContext("2d")
        ctx.reset()

        ctx.beginPath();
        for (var i = 0 ; i < maze.length; i++) {
            let x = (i % gridSizeWidth.value) * cellXSize;
            let y = Math.floor(i / gridSizeWidth.value) * cellYSize;

            if (!gridView.isSet(maze[i], 0)) {
                ctx.moveTo(x + cellXSize, y);
                ctx.lineTo(x + cellXSize, y + cellYSize);
            }
            if (!gridView.isSet(maze[i], 1)) {
                ctx.moveTo(x, y + cellYSize);
                ctx.lineTo(x + cellXSize, y + cellYSize);
            }
            if (!gridView.isSet(maze[i], 2)) {
                ctx.moveTo(x, y);
                ctx.lineTo(x, y + cellYSize);
            }
            if (!gridView.isSet(maze[i], 3)) {
                ctx.moveTo(x, y);
                ctx.lineTo(x + cellXSize, y);
            }
        }
        ctx.stroke();
    }
}
