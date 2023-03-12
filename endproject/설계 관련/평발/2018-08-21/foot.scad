 scale([1, 1, 0.15])
surface(file = "foot_01.png", center = false, invert = true);
//
// This will turn a scanned foot image into a zheight surface and then profile clipped.
//
dxf_profile = "Scan10001.dxf";
dxf_profile_offset = 3;
scanned_image_file = "foot_01.png";
zscale = 0.15; // Varies the height exaggeration
zinvert = true; // false will create a male version of the imported image
xoffset=25; // BUG : Don't know why the DXF files have been offset by this random amount
yoffset=-30; // BUG : Don't know why the DXF files have been offset by this random amount

intersection ()
{
        translate ([xoffset,yoffset,-20])
        {
#              linear_extrude (100)
                {
                        offset(dxf_profile_offset, join_type = "round")
                        {
                                import(file = dxf_profile, convexity = 12);
                        }
                }
        }
        scale([1,1, zscale])
#      surface(file = scanned_image_file, center = false, invert = zinvert);
}