
; vesa_info is 1-byte packed -> no need for padding
vesa_info STRUCT
    vbe_signature db 4 dup (?)
    vbe_version dw ?
    oem_string_ptr dd ?
    capabilities db 4 dup (?)
    videomode_ptr dd ?
    memory dw ?
    oem_software_rev dw ?
    oem_vendor_name_ptr dd ?
    oem_product_name_ptr dd ?
    oem_product_rev_ptr dd ?
    reserved db 222 dup(?)
    oem_data db 256 dup(?)
vesa_info ENDS

IF SIZEOF vesa_info NE 200h
    ERR <vesa_info size mismatch!>
ENDIF

vesa_scanline STRUCT
    _offset dd ?
    _page dd ?
    split dd ?
    _pad dd ?
vesa_scanline ENDS

IF SIZEOF vesa_scanline NE 16
    ERR <vesa_scanline size mismatch!>
ENDIF

; vesa_work is NOT packed -> padding
vesa_work STRUCT
    window_start dd ?
    selector dw ?
    _padding_0x06 dw ?
    window_end dd ?
    scanline_max dd ?
    scanline_table dd ?
    pixel_size dd ?
    full_banks dd ?
    bytes_left dd ?
    bank_increment dd ?
    scanlines_per_page dd ?
    scanlines_remainder dd ?
    page_size dd ?
    stride dd ?
    current_page dd ?
    access_linear dd ?
    bank_protected dd ?
    scanline_breaks dw ?
    _padding_0x42 dw ?
    bank_function dd ?
    physical_selector dw ?
    _padding_0x4a dw ?
    physical_address dd ?
    linear dd ?
vesa_work ENDS

IF SIZEOF vesa_work NE 54h
    ERR <vesa_work size mismatch!>
ENDIF

; br_device is NOT packed -> padding
br_device STRUCT
    dispatch dd ?
    identifier dd ?
    object_list dd ?
    res dd ?
    original_mode dw ?
    version_limit dw ?
	use_pmi dd ?
	use_linear dd ?
	set_stride dd ?
	current_mode dw ?
    info vesa_info <>
	_pad_0x222 dw ?
    work vesa_work <>
    clut dd ?
    screen_active dd ?
br_device ENDS

IF SIZEOF br_device NE 280h
    ERR <br_device size mismatch!>
ENDIF

extern DriverDeviceVESA:br_device
