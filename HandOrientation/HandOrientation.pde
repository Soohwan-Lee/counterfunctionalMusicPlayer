import de.voidplus.leapmotion.*;
import hypermedia.net.*;
import processing.serial.*;



Serial Port;
//Serial Port2;

LeapMotion leap;
UDP udp;

int count = 0;
int temp = 0;
boolean t = true;

int savedTime = 0;
int totalTime = 3000;
//int passedTime = 0;

// UDP variables
String ip       = "192.168.43.121";
int port        = 12000;    // the destination port

void setup() {
  Port = new Serial(this, Serial.list()[4], 9600);
  //Port2 = new Serial(this, Serial.list()[5], 9600);

  size(800, 500);
  background(255);
  // ...

  leap = new LeapMotion(this).allowGestures();

  udp = new UDP( this, 6000 );
  udp.listen( true );
}

void draw() {
  background(255);
  // ...



  //int fps = leap.getFrameRate();
  for (Hand hand : leap.getHands ()) {

    boolean handIsLeft         = hand.isLeft();
    boolean handIsRight        = hand.isRight();

    // ==================================================
    // 4. Finger

    Finger  fingerThumb        = hand.getThumb();
    // or                        hand.getFinger("thumb");
    // or                        hand.getFinger(0);

    Finger  fingerIndex        = hand.getIndexFinger();
    // or                        hand.getFinger("index");
    // or                        hand.getFinger(1);

    Finger  fingerMiddle       = hand.getMiddleFinger();
    // or                        hand.getFinger("middle");
    // or                        hand.getFinger(2);

    Finger  fingerRing         = hand.getRingFinger();
    // or                        hand.getFinger("ring");
    // or                        hand.getFinger(3);

    Finger  fingerPink         = hand.getPinkyFinger();
    // or                        hand.getFinger("pinky");
    // or                        hand.getFinger(4);


    for (Finger finger : hand.getOutstretchedFingers()) {
      // or              hand.getOutstretchedFingers();
      // or              hand.getOutstretchedFingersByAngle();

      //int     fingerId         = finger.getId();
      //PVector fingerPosition   = finger.getPosition();
      //PVector fingerStabilized = finger.getStabilizedPosition();
      //PVector fingerVelocity   = finger.getVelocity();
      //PVector fingerDirection  = finger.getDirection();
      //float   fingerTime       = finger.getTimeVisible();

      boolean thumb = fingerThumb.isExtended();
      boolean index = fingerIndex.isExtended();
      boolean middle = fingerMiddle.isExtended();
      boolean ring = fingerRing.isExtended();
      boolean pink = fingerPink.isExtended();

      finger.drawBones();


      //println("Is Thumb Extended " + thumb);
      //if (handIsLeft == true && index == true && thumb == false && middle == false && ring == false&&  pink == false) {



      //if (handIsLeft == true && finger.getType() == 1) {
      //  println("Fucking");
      //  //if (handIsRight == true && index == true && thumb == false && middle == false && ring == false&&  pink == false) {
      //  if (handIsRight == true) {
      //    if (finger.getType() == 1) {
      //    count = 11;
      //    println("Fucking Number of fingers: " + count);
      //    }
      //  }
      //} else {
      //count = 0;
      if (handIsRight == true) {
        if (thumb)
          count++;
        else if (index)
          count++;
        else if (middle)
          count++;
        else if (ring)
          count++;
        else if (pink)
          count++;
      } else if (handIsLeft == true) {
        if (thumb)
          count++;
        else if (index)
          count++;
        else if (middle)
          count++;
        else if (ring)
          count++;
        else if (pink)
          count++;
      }
    }
  }
  if (count > 0) {
    if (t == true) {
      savedTime = millis();
      temp = count;
      t = false;
      println("Start!  " + temp);
    }
    int passedTime = millis() - savedTime;
    //println("Passed Time: "+passedTime);
    //println("Number of fingers: " + count);
    if (passedTime > totalTime) {
      if (temp == count) {
        //udp.send(str(count), ip, port );
        //Port.write(count);
        t = true;
        println("Success!");
      } else if (temp !=count) {
        t = true;
        println("Fail!");
      }
    }
  }
  if (count == 0) {
    t = true;
  }

  count = 0;
  //temp = 0;
  if (keyPressed) {
    if (key == 'a' || key == 'A') {
      Port.write(11);
      println("Start! " + str(11));
      println("Success!");
    }
    if (key == 'b' || key == 'B') {
      Port.write(12);
      println("Start! " + str(12));
      println("Success!");
    }
    if (key == '1') {
      Port.write(13);
      println("Start! " + str(13));
      delay(2000);
      println("Success!");
    }
    if (key == '2') {
      Port.write(14);
      println("Start! " + str(14));
      delay(2000);
      println("Success!");
    }
    if (key == '9') {
      Port.write(4);
      delay(2000);
      println("Start! " + str(4));
      println("Success!");
    }
    if (key == '0') {
      Port.write(12);
      delay(2000);
      println("Start! " + str(12));
      println("Success!");
    }
  }
}
