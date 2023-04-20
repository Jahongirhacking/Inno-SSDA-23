// Jahongir Hayitov CS-01
// J.Hayitov@innopolis.university

import java.io.File;

class Logging {
    private static Logging instance = null;
    private  Logging() {};
    private File file;
    StringBuilder fileData = new StringBuilder();
    public static Logging getInstance(){
        synchronized(Logging.class){
            if(instance==null){
                instance = new Logging();
            }
        }
        return instance;
    }
    public void writeToFile(ProcessData data) {
        if(instance!=null) {
            fileData = new StringBuilder(data.toString());
            System.out.println("Writing to the file: " + fileData);
        }
    }
    public void readFromFile() {
        if(instance!=null ) {
            System.out.println("Reading from the file: " + fileData);
        }
    }
    public void appendToFile(ProcessData data) {
        if(instance!=null) {
            fileData.append(data.toString());
            System.out.println("Appending to the file: " + fileData);
        }
    }
    public void deleteFile() {
        if(instance!=null) {
            fileData = new StringBuilder();
            System.out.println("Deleting the file");
        }
    }
}

abstract class Monitoring {
    public Logging logging;
    Monitoring() {
        logging = Logging.getInstance();
    }
    public abstract void logData(ProcessData data);
    public abstract void visualizeData();
}

abstract class MonitoringFactory {
    public Monitoring returnMonitoring() {
        Monitoring monitoring = createMonitoring();
        return monitoring;
    }
    public abstract Monitoring createMonitoring();
}

class SystemProcessesMonitoringFactory extends MonitoringFactory {
    @Override
    public Monitoring createMonitoring() {
        return new SystemProcessesMonitoring();
    }
}

class UserProcessesMonitoringFactory extends MonitoringFactory {
    @Override
    public Monitoring createMonitoring() {
        return new UserProcessesMonitoring();
    }
}

class UserProcessesMonitoring extends Monitoring{
    public UserProcessesMonitoring() {}

    @Override
    public void logData(ProcessData data) {
        System.out.println("User Monitoring: ");
        logging.writeToFile(data);
    }

    @Override
    public void visualizeData() {
        System.out.println("User Monitoring: ");
        logging.readFromFile();
    }
}

class SystemProcessesMonitoring extends Monitoring {
    public SystemProcessesMonitoring() {}
    @Override
    public void logData(ProcessData data) {
        System.out.println("System Monitoring: ");
        logging.writeToFile(data);
    }

    @Override
    public void visualizeData() {
        System.out.println("System Monitoring: ");
        logging.readFromFile();
    }
}

class ProcessData {
    private long PID;
    private double SHR;
    private double VIRT;
    private double CPU;
    private String OwnerName;
    private long NI;
    private String permissions;
    public ProcessData(){}

    public long getPID() {
        return PID;
    }

    public void setPID(long PID) {
        this.PID = PID;
    }

    public double getSHR() {
        return SHR;
    }

    public void setSHR(double SHR) {
        this.SHR = SHR;
    }

    public double getVIRT() {
        return VIRT;
    }

    public void setVIRT(double VIRT) {
        this.VIRT = VIRT;
    }

    public double getCPU() {
        return CPU;
    }

    public void setCPU(double CPU) {
        this.CPU = CPU;
    }

    public String getOwnerName() {
        return OwnerName;
    }

    public void setOwnerName(String ownerName) {
        OwnerName = ownerName;
    }

    public long getNI() {
        return NI;
    }

    public void setNI(long NI) {
        this.NI = NI;
    }

    public String getPermissions() {
        return permissions;
    }

    public void setPermissions(String permissions) {
        this.permissions = permissions;
    }

    @Override
    public String toString() {
        StringBuilder string = new StringBuilder();
        string.append("{ PID = " + PID);
        string.append(", SHR = " + SHR);
        string.append(", VIRT = " + VIRT);
        string.append(", CPU = " + CPU);
        string.append(", OwnerName = " + OwnerName);
        string.append(", NI = " + NI);
        string.append(", permissions = " + permissions + " }");
        return string.toString();
    }
}

interface IBuilder {
    public void init();
    public void setPID(long PID);
    public void setSHR(double SHR);
    public void setCPU(double CPU);
    public void setOwnerName(String ownerName);
    public void setVIRT(double VIRT);
    public void setNI(long NI);
    public void setPermissions(String permissions);
    public ProcessData build();
}

class ProcessDataBuilder implements IBuilder {
    ProcessData processData;
    @Override
    public void init() {
        this.processData = new ProcessData();
    }
    @Override
    public void setPID(long PID) {
        processData.setPID(PID);
    }
    @Override
    public void setSHR(double SHR) {
        processData.setSHR(SHR);
    }
    @Override
    public void setCPU(double CPU) {
        processData.setCPU(CPU);
    }
    @Override
    public void setOwnerName(String ownerName) {
        processData.setOwnerName(ownerName);
    }
    @Override
    public void setVIRT(double VIRT) {
        processData.setVIRT(VIRT);
    }
    @Override
    public void setNI(long NI) {
        processData.setNI(NI);
    }
    @Override
    public void setPermissions(String permissions) {
        processData.setPermissions(permissions);
    }
    @Override
    public ProcessData build() {
        return processData;
    }
}

public class Task_3 {
    public static void main(String[] args) {
        UserProcessesMonitoringFactory userFactory = new UserProcessesMonitoringFactory();
        SystemProcessesMonitoringFactory systemFactory = new SystemProcessesMonitoringFactory();

        // Creating ProcessData
        ProcessDataBuilder builder = new ProcessDataBuilder();
        builder.init();
        builder.setPID(1289376);
        builder.setSHR(12.5);
        builder.setVIRT(3.2);
        builder.setCPU(10.4);
        builder.setOwnerName("Ozoda");
        builder.setNI(12);
        builder.setPermissions("some permission");
        ProcessData processData = builder.build();

        // Monitoring Process
        Monitoring userMonitoring = userFactory.createMonitoring();
        userMonitoring.logData(processData);
        userMonitoring.visualizeData();

        Monitoring systemMonitoring = systemFactory.createMonitoring();
        systemMonitoring.logData(processData);
        systemMonitoring.visualizeData();
    }
}