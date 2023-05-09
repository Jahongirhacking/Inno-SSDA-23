//Jahongir Hayitov CS-01
//J.Hayitov@innopolis.university

import java.util.*;

interface Subject {
    public void subscribe(Observer o);
    public void unsubscribe(Observer o);
    public void notifySubscribers();
}

interface Observer {
    public void update(Content content);
    public void display();
}

interface Content {
    public String getContentName();
    public void setChannel(Channel channel);
    public Channel getChannel();
    public String displayMessage();
}

class Channel implements Subject {
    private ArrayList<Observer> observers;
    private Content content;
    private String channelName;
    
    // Create list for observers
    public Channel(String channelName) {
        this.channelName = channelName;
        observers = new ArrayList<Observer>();
    }
    // Register new observers
    public void subscribe(Observer o) {
        observers.add(o);
    }
    // Remove observers
    public void unsubscribe(Observer o) {
        int index = observers.indexOf(o);
        if(index>=0) observers.remove(index);
    }
    // Notify all observers
    public void notifySubscribers() {
        for(Observer o : observers) {
            o.update(this.content);
        }
    }
    
    public void contentPublished() {
        notifySubscribers();
    }
    
    public void publish(Content content) {
    	//  Receive the content and set its channel info
        this.content = content;
        content.setChannel(this);
        contentPublished();
    }
    
    public String getChannelName() {
        return this.channelName;
    }
}

class Video implements Content {
    Channel channel;
    String contentName;
    String contentType = "Video";
    public Video(String contentName) {
        this.contentName = contentName;
    }
    @Override
    public void setChannel(Channel channel) {
        this.channel = channel;
    }
    @Override
    public Channel getChannel() {
        return this.channel;
    }
    @Override
    public String getContentName() {
        return this.contentName;
    }
    @Override
    public String displayMessage() {
        return " published new "+this.contentType;
    }
}

class Shorts implements Content {
    Channel channel;
    String contentName;
    String contentType = "Shorts";
    public Shorts(String contentName) {
        this.contentName = contentName;
    }
    @Override
    public void setChannel(Channel channel) {
        this.channel = channel;
    }
    @Override
    public Channel getChannel() {
        return this.channel;
    }
    @Override
    public String getContentName() {
        return this.contentName;
    }
    @Override
    public String displayMessage() {
        return " published new "+this.contentType;
    }
}

class LiveStream implements Content {
    Channel channel;
    String contentName;
    String contentType = "LiveStream";
    public LiveStream(String contentName) {
        this.contentName = contentName;
    }
    @Override
    public void setChannel(Channel channel) {
        this.channel = channel;
    }
    @Override
    public Channel getChannel() {
        return this.channel;
    }
    @Override
    public String getContentName() {
        return this.contentName;
    }
    @Override
    public String displayMessage() {
        return " is going live";
    }
}

class User implements Observer {
    Channel channel;
    Content content;
    String userName;
    public User(String userName) {
        this.userName = userName;
    }
    @Override
    public void update(Content content) {
        this.content = content;
        this.channel = content.getChannel();
        display();
    }
    @Override
    public void display() {
        System.out.println(userName+": Channel "+channel.getChannelName()+
        content.displayMessage()+": "+content.getContentName());
    }
}


public class Runner {
    public static void main(String[] args) {
        // Create some users
        User user1 = new User("Alice");
        User user2 = new User("Bob");
        // Create some channels
        Channel channel1 = new Channel("Discovery");
        Channel channel2 = new Channel("Pewdiepie");
        Channel channel3 = new Channel("Innopolis");
        // Subscribe users
        channel1.subscribe(user1);
        channel2.subscribe(user2);
        channel3.subscribe(user1);
        channel3.subscribe(user2);
        // Publish
        channel1.publish(new Video("Animals in Australia"));
        channel2.publish(new Shorts("Minicraft"));
        channel3.publish(new LiveStream("Report from rainforest"));
        // Unsubscribe
        channel3.unsubscribe(user1);
        // Publish
        channel1.publish(new Video("Scuba diving in Great Barrier Reef"));
        channel2.publish(new Shorts("Fortnite montage"));
        channel3.publish(new LiveStream("Jungle survival tips"));
    }
}
