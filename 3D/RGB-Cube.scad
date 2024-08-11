/*
*******************************************
Objekt Info: RGB-Cube

*******************************************
Version: 09.08.2024 khf
*******************************************
*/

//***************   Auswahl   *************


//*****************************************

//***************   Libraries  ************


//*****************************************

//***************  Parameter   *************



//cube dimensions
size_cube = 80; //edge length of the cube
th_cube = 4;    //thickness of the cube
r_cube = 8;     //radius of the corners


//led dimensions
size_led = 65 + 1;  //length of the leds edge
th_led = 3;         //thickness of the led. must be less than th_cube
overlap_led = 2;    //to avoid the led to fall into the cube
size_base = 160;    //size of cube to cut base

//usb_y = 8;
//usb_z = 4;
d_dcjack = 8;       // 8 diameter of dc jack connector !!!

d_ir = 0;           // 4 diameter of hole for ir receiver !!!

//to calculate angle of rotation to get the right position
distance_h = (sqrt(2) * size_cube ) / 2;
distance_v = size_cube / 2;
angle_y = atan(distance_h/distance_v);
//echo(angle_y);

   $fn = 64;
//*********************************************   
   

pos_cube_corner = [[(size_cube / 2) - r_cube,-(size_cube / 2) + r_cube, -(size_cube / 2) + r_cube],
                   [size_cube / 2 - r_cube, (size_cube / 2)- r_cube, -(size_cube / 2)+ r_cube],
                   [-(size_cube / 2)+ r_cube, (size_cube / 2)- r_cube, -(size_cube / 2)+ r_cube],
                   [-(size_cube / 2)+ r_cube, -(size_cube / 2)+ r_cube, -(size_cube / 2)+ r_cube],
                   [size_cube / 2- r_cube, -(size_cube / 2)+ r_cube, (size_cube / 2)- r_cube],
                   [size_cube / 2- r_cube, (size_cube / 2)- r_cube, (size_cube / 2)- r_cube],
                   [-(size_cube / 2)+ r_cube, (size_cube / 2)- r_cube, (size_cube / 2)- r_cube],
                   [-(size_cube / 2)+ r_cube, -(size_cube / 2)+ r_cube, (size_cube / 2)- r_cube]
                   ];


difference(){
    
    translate([0,0,35])  //TO DO change it to parametric
    rotate([0,angle_y,0])
    rotate([0,0,45])
    //cube(size_cube,center = true);
    cube_mod();
    
    translate([-size_base/2,-size_base/2,-size_base])   //cut base of the cube
    cube(size_base,center = false);
    
    translate([0,0,size_cube ]) //cut hole for ir receiver
    cylinder(d = d_ir, h = size_cube,center = true, $fn = 32);
}

module cube_mod(){
    difference(){
        //cube(size_cube,center = true);
        cube_round();
        
        difference(){       //make the cube hollow
            cube(size_cube-th_cube * 2,center = true);
            
            translate([42.5,-42.5,-42.5]) //TO DO automatized with thickness instead this
            rotate([0,0,45])
            rotate([-angle_y,0,0])
            cylinder(h = size_cube,d = 2 * size_cube,center = true);
        }
        
        translate([-(size_cube / 2),0,0]){  //cut holes for the leds panels
            cube(size_led - 2 * overlap_led, center = true);
            translate([th_led / 2,0,0])
            cube([th_led,size_led,size_led],center = true);
        }
        translate([0,size_cube / 2,0]){
            cube(size_led - 2 * overlap_led, center = true);
            translate([0,-th_led / 2,0])
            cube([size_led,th_led,size_led],center = true);
        }
        translate([0,0,size_cube / 2]){
            cube(size_led - 2 * overlap_led, center = true);
            translate([0,0,-th_led / 2])
            cube([size_led,size_led,th_led],center = true);
        }
           rotate([0,90,0])
     //      translate([size_cube / 0,8,10])    //cut hole for dc jack

        //cube([size_cube,usb_y,usb_z],center = true);
         translate([ -23,23 ,0])
        cylinder(d = d_dcjack, h = size_cube, $fn = 32);
    }
    

               
  
    
    
//    translate([-6,-(40-9-5),6])
//    rotate([0,45,0])
//    battery();
//    translate([40-9-5,6,6])
//    rotate([45,0,0])
//    battery();
//    translate([-6,6,-(40-9-5)])
//    rotate([90,0,-45])
//    battery();
}

module cube_round(){
    hull(){
        for(a = pos_cube_corner){
            translate(a)
            sphere(r_cube);
            }
        }
}

module battery(){
    color("green")
    cylinder(h = 65,d = 18,center = true, $fn = 32);
}
