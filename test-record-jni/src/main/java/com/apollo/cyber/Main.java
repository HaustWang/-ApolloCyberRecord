package com.apollo.cyber;

public class Main {
    public static void main(String[] args) {
        System.out.println("Hello world!");

        NarSystem.loadLibrary();
        //        try {
        RecordReader reader = new RecordReader();
        reader.createReader("demo_3.5.record");

        String[] channelList = reader.getChannelList();
        for (String channel : channelList) {
            System.out.println(channel);
        }
//        } catch (Exception e) {
//            e.printStackTrace();
//        }
    }
}