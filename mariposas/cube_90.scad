// Empty cone
module cone(length,angle){
    difference() {
        cylinder(h=length,r1=0,r2=length*tan(angle/2),center=false);
        translate([0,0,0.01*length]) cylinder(h=length,r1=0,r2=length*tan(angle/2),center=false);    
    }
}


// Edges of a cube
module cubeframe(length,centr) {
    translate(centr)
    difference() {
        cube(length,center=true);
        union() {
            slen=0.95*length;
            blen=1.02*length;
            cube([blen,slen,slen],center=true);
            cube([slen,blen,slen],center=true);
            cube([slen,slen,blen],center=true);
        }
    }
}

// Field of view
module fieldofview(length,angle,ratio,rotangle) {
    radius=length*tan(angle/2);
    theta=atan(1/ratio);
    x=radius*cos(theta);
    y=radius*sin(theta);
    
    vfov=2*atan(y/length);
    hfov=2*atan(x/length);
    
    echo("vfov=",vfov);
    echo("hfov=",hfov);
    
    rotate(rotangle,[0,0,1])
    polyhedron(
      points = [[0,0,0],        // 0
                [x,y,length],   // 1
                [-x,y,length],  // 2
                [-x,-y,length], // 3
                [x,-y,length]  // 4
               ],  
      faces = [[0,1,2],[0,2,3],[0,3,4],[0,4,1]]);
}

module filledfieldofview(length,angle,ratio,rotangle) {
    radius=length*tan(angle/2);
    theta=atan(1/ratio);
    x=radius*cos(theta);
    y=radius*sin(theta);
    xm=x-m;
    ym=y-m;
    d=0.05*length;
    rotate(rotangle,[0,0,1])
    polyhedron(
      points = [[0,0,0],        // 0
                [x,y,length],   // 1
                [-x,y,length],  // 2
                [-x,-y,length], // 3
                [x,-y,length]   // 4
               ],  
      faces = [[0,1,2],[0,2,3],[0,3,4],[0,4,1],[1,3,2],[1,4,3]]);
}

module fov(length,aspectratio,vfov,rotangle) {
    
    v = length*tan(vfov/2);
    r = v*sqrt(1+aspectratio*aspectratio);
    alpha = 2*atan(r/length);
    echo("alpha=",alpha);
    
    fieldofview(length,alpha,aspectratio,rotangle);
}

module ffov(length,aspectratio,vfov,rotangle) {
    
    v = length*tan(vfov/2);
    r = v*sqrt(1+aspectratio*aspectratio);
    alpha = 2*atan(r/length);
    
    filledfieldofview(length,alpha,aspectratio,rotangle);
}


module blindSpotA(length) {
    d = length*0.0005;
    rl = 0.999*length;

    difference() {
        translate([d,d,d]) cube(rl);
        rotate(45,[-1,1,0]) ffov(length*sqrt(3),1/aspectratio,90,-45);
    }
}

module blindSpotB(length) {
    d = length*0.0005;
    rl = 0.999*length;

    difference() {
        translate([d,d,d]) cube(rl);
        translate([length,0,length]) rotate(a=-135,v=[1,1,0]) ffov(length*sqrt(3),1/aspectratio,90,45);
        //translate([length,0,length]) rotate(a=-126.87,v=[1,1,0]) ffov(length*sqrt(3),1/aspectratio,90,-45);
    }
}

module blindSpotC(length) {
    d = length*0.0005;
    rl = 0.999*length;

    difference() {
        translate([d,d,d]) cube(rl);
        translate([0,length,length]) rotate(a=135,v=[1,1,0]) ffov(length*sqrt(3),1/aspectratio,90,45);
    }
}

// Blindspots for 3D reconstruction
module blindSpots(length) {

    intersection() {
        union() { blindSpotA(length); blindSpotB(length); }
        blindSpotC(length);
    }

    intersection() {
        union() { blindSpotB(length); blindSpotC(length); }
        blindSpotA(length);
    }

    intersection() {
        union() { blindSpotA(length); blindSpotC(length); }
        blindSpotB(length);
    }
}

module totalBlindSpot(length) {
    intersection() { blindSpotA(length); blindSpotB(length); }
    intersection() { blindSpotB(length); blindSpotC(length); }
    intersection() { blindSpotA(length); blindSpotC(length); }
}

aspectratio=4/3;   

// Cube frame
color("blue",0.25) cubeframe(100,[50,50,50]);

//color("yellow",0.25)
//intersect() {
//   rotate(45,[-1,1,0]) ffov(100*sqrt(3),1/aspectratio,90,-45);
//   translate([100,0,100]) rotate(a=-135,v=[1,1,0]) ffov(100*sqrt(3),1/aspectratio,90,45);
//}

color("gray",0.05) blindSpots(100);
//color("gray",0.05) totalBlindSpot(100);


// Main, reference camera
rotate(45,[-1,1,0]) {
    color("red",0.25) fov(100*sqrt(3),1/aspectratio,90,-45);
    color("red",1) {
        cylinder(h=200,r1=0.5,r2=0.5);
        sphere(5); 
    }
}


// Mode 1
translate([100,0,100]) 
rotate(a=-135,v=[1,1,0]) {
    //color("green",0.25) fov(100*sqrt(3),1/aspectratio,90,45);
    color("green",1) {
        cylinder(h=200,r1=0.5,r2=0.5);
        sphere(5);
    }
}


translate([0,100,100]) 
rotate(a=135,v=[1,1,0]) {
    //color("blue",0.25) fov(100*sqrt(3),1/aspectratio,90,45);
    color("blue",1) {
        cylinder(h=200,r1=0.5,r2=0.5);
        sphere(5);
    }
}

//$vpt=[ 100, 100, 100 ];
//$vpd=330;
//$vpr=[ 135.00, 0.00, 315 ];
