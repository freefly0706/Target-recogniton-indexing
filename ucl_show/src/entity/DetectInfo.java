package entity;

public class DetectInfo {
    private String objectClass;
    private int localXMIN;
    private int localYMIN;
    private int localXMAX;
    private int localYMAX;
    private float score;

    public DetectInfo() {
    }

    public DetectInfo(String objectClass, int localXMIN, int localYMIN, int localXMAX,
                      int localYMAX, float score, float imageSize) {
        this.objectClass = objectClass;
        this.localXMIN = localXMIN;
        this.localYMIN = localYMIN;
        this.localXMAX = localXMAX;
        this.localYMAX = localYMAX;
        this.score = score;
    }

    public String getObjectClass() {
        return objectClass;
    }

    public void setObjectClass(String objectClass) {
        this.objectClass = objectClass;
    }

    public int getLocalXMIN() {
        return localXMIN;
    }

    public void setLocalXMIN(int localXMIN) {
        this.localXMIN = localXMIN;
    }

    public int getLocalYMIN() {
        return localYMIN;
    }

    public void setLocalYMIN(int localYMIN) {
        this.localYMIN = localYMIN;
    }

    public int getLocalXMAX() {
        return localXMAX;
    }

    public void setLocalXMAX(int localXMAX) {
        this.localXMAX = localXMAX;
    }

    public int getLocalYMAX() {
        return localYMAX;
    }

    public void setLocalYMAX(int localYMAX) {
        this.localYMAX = localYMAX;
    }

    public float getScore() {
        return score;
    }

    public void setScore(float score) {
        this.score = score;
    }

    @Override
    public String toString() {
        return "DetectInfo{" +
                "objectClass='" + objectClass + '\'' +
                ", localXMIN=" + localXMIN +
                ", localYMIN=" + localYMIN +
                ", localXMAX=" + localXMAX +
                ", localYMAX=" + localYMAX +
                ", score=" + score +
                '}';
    }
}
