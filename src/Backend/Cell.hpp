namespace Grid {

struct Cell {
    enum class Type {
        EmptyField,
        Obstacle,
        Start,
        End
    };

    Cell(int id, int type);

    int id;
    Type type;
private:
    Type toType(int type) const;
};

}
