

module feather_epd_screwhole() {
    difference() {
        union() {
            translate([0,-1,0]) {
                cube([5,3.5,1]);
            }
            translate([2.5,2.5,0]) {
                cylinder(h=1, d=5, center=false, $fn=50);
            }
        }
        translate([2.5,2.5,0]) {
            cylinder(h=3, d=4.5, center=true, $fn=50);
        }
    }
}

module feather_epd_footprint() {
    union() {
        cube([60, 30, 20]);
        translate([5,0,0]) rotate(180) {
            feather_epd_screwhole();
        }
        translate([60, 0, 0]) rotate(180) {
            feather_epd_screwhole();
        }
        translate([0,30,0]) {
            feather_epd_screwhole();
        }
        translate([55,30,0]) {
            feather_epd_screwhole();
        }
    }
}


module component_mount_screwhole() {
    translate([2.5,2.5,0]) {
        cylinder(d=4, h=12, center=true, $fn=50);
    }
}
module component_mount_screwmount() {
    difference() {
        cube([5,5,5]);
        component_mount_screwhole();
    }
}
module button_mount_negative() {
    union() {
        cube([8,8,3]);
        cube([2,8,10]);
        translate([6,0,0]) cube([2,8,10]);
    }
}

module component_mount() {
    union() {
        difference() {
            cube([90,125, 30]); 

            // empty space in the bottom
            translate([10,-5,3]) cube([70,  92+5, 32]);

            // empty space in the sides
            translate([-1,5,3]) cube([100, 92-5, 32]);

            // area for power line
            translate([5,10,-1]) cube([80, 15, 32]);

            // area for lower line
            translate([5,30,-1]) cube([80, 20,32]);

            // screen
            translate([5,55,-1]) cube([70, 32, 32]);
            translate([7,50,-1]) cube([10,10,3]);
            translate([7,82,-1]) cube([10,10,3]);
            translate([7+53,50,-1]) cube([10,10,3]);
            translate([7+53,82,-1]) cube([10,10,3]);
            
            // buttons
            translate([78,57,-1]) button_mount_negative(); 
            translate([78,66.5,-1]) button_mount_negative();
            translate([78,77,-1]) button_mount_negative();

            // area for power adapter
            translate([5,92+2,-1]) cube([80, 35,32]);
            
            // sides of power adapter
            translate([-1,97,2]) cube([95,20,32]);

            // reduced depth of power adapter
            translate([-1,89,25]) cube([95,25,10]);
        }

        // support for power adapter
        translate([15,92.9,0]) cube([2,5,25]);
        translate([15+35,92.9,0]) cube([2,5,25]);

        // support for temp sensor
        translate([40,40,2]) cube([20,12,1]);
        
        // support for line connector
        translate([35,0,3]) cube([20,1,20]);

        translate([0,5,25]) component_mount_screwmount();
        translate([85,5,25]) component_mount_screwmount();
        translate([0,112,25]) component_mount_screwmount();
        translate([85,112,25]) component_mount_screwmount();
    }
}

module wall_mount() {
    union() {
        difference() {
            cube([90,125, 3]); 
            translate([(90/2)-(50.8/2),(125/2)-(75/2),-1])
                cube([50.8,75,5]);
            translate([0,0,-28]) component_mount();
            translate([(90/2),(125/2)-(83.34/2),-1])
                cylinder(h=5,d=3.5,$fn=50);
            translate([(90/2),(125/2)+(83.34/2),-1])
                cylinder(h=5,d=3.5,$fn=50);
            translate([0,5,-1]) component_mount_screwhole();
            translate([85,5,-1]) component_mount_screwhole();
            translate([0,112,-1]) component_mount_screwhole();
            translate([85,112,-1]) component_mount_screwhole();
        }
    }
}

module external_cover() {
    union() {
        difference() {
            translate([-3,-3,-2]) cube([96,131, 33]); 
            translate([-1,-1,0]) cube([92,127, 35]);
            
            translate([77,56.5,-5]) cube([10, 29, 33]);

            translate([5,51,-1]) cube([70, 91-51, 28.5]);
            translate([11,60,-5]) cube([50, 23, 28.5]);
            difference() {
                union() {
                    // front grills
                    difference() {
                        for (i=[5:4:86]) {
                            translate([i,92,-5]) cube([1.5,55,30]);
                            translate([i,-5,-5]) cube([1.5,55,30]);
                        }
                        translate([-4,-4,-5]) cube([120,10,10]);
                        translate([-4,120,-5]) cube([120,10,10]);
                    }
                    // side grills
                    for (i=[5:6:115]) {
                        translate([-5,i,5]) cube([10,3,20]);
                        translate([90,i,5]) cube([10,3,20]);
                    }
                }
                translate([-5,-5,15-1.5]) cube([100,150,3]);
            }
        }
    }
}

//mirror([0,0,1]) {
    
    //translate([0,0,28])
    //    wall_mount();
    
    //mirror([0,0,1])
    //translate([0,0,-27])
        //component_mount();
    //translate([0,0,-30])
        external_cover();
//}