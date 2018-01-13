package entity;

public class UCLInfo {
    private String ucl;
    private String uclSign;
    private float uclKByte;
    private String uclTimeStamp;

    public UCLInfo() {
    }

    public String getUcl() {
        return ucl;
    }

    public void setUcl(String ucl) {
        this.ucl = ucl;
    }

    public String getUclSign() {
        return uclSign;
    }

    public void setUclSign(String uclSign) {
        this.uclSign = uclSign;
    }

    public float getUclKByte() {
        return uclKByte;
    }

    public void setUclKByte(float uclKByte) {
        this.uclKByte = uclKByte;
    }

    public String getUclTimeStamp() {
        return uclTimeStamp;
    }

    public void setUclTimeStamp(String uclTimeStamp) {
        this.uclTimeStamp = uclTimeStamp;
    }

    @Override
    public String toString() {
        return "UCLInfo{" +
                "ucl='" + ucl + '\'' +
                ", uclSign='" + uclSign + '\'' +
                ", uclKByte=" + uclKByte +
                ", uclTimeStamp='" + uclTimeStamp + '\'' +
                '}';
    }
}
