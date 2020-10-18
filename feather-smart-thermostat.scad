

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
    difference() {
        cube([5,5,5]);
        translate([2.5,2.5,0]) {
            cylinder(d=4, h=12, center=true, $fn=50);
        }
    }
}

module button_mount_negative() {
    union() {
        cube([8,8,31]);
        cube([2,8,10]);
        translate([6,0,0]) cube([2,8,10]);
    }
}

module component_mount() {
    difference() {
        union() {
            cube([90,80, 5]); 
            cube([5,80,30]);
            translate([85,0,0]) cube([5,80,30]);
            translate([0,-5,25]) component_mount_screwhole();
            translate([85,-5,25]) component_mount_screwhole();
            translate([0,80,25]) component_mount_screwhole();
            translate([85,80,25]) component_mount_screwhole();
        }
        translate([-1,5,3]) cube([100, 70, 30]);
        translate([5,10,-1]) cube([80, 15, 10]);
        translate([5,35,-1]) cube([80, 5,10]);
        translate([5,45,-1]) cube([70, 29, 10]);
        translate([78,45,-1]) button_mount_negative(); 
        translate([78,55.5,-1]) button_mount_negative();
        translate([78,66,-1]) button_mount_negative();
    }
}


component_mount();