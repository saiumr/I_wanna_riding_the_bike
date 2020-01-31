package MapEditor.src;

class Collision {
    public static boolean PointInRect(int px, int py, int rx, int ry, int rw, int rh){
        return (px>rx && px<rx+rw && py>ry && py<ry+rh);
    }

    public static boolean RectEqual(int r1x, int r1y, int r1w, int r1h, int r2x, int r2y, int r2w, int r2h){
        return r1x==r2x && r1y==r2y && r1w==r2w && r1h==r2h;
    }

    public static boolean RectColliedRect(int r1x, int r1y, int r1w, int r1h, int r2x, int r2y, int r2w, int r2h){
        //TODO 未完成
        return false;
    }
}
