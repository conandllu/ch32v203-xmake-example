-- 设置工程名
set_project("ch32v203-xmake")

-- 设置工程版本
set_version("1.0.0")

add_rules("mode.debug", "mode.release")

-- 自定义工具链
toolchain("riscv-none-embed")
    -- 标记为独立工具链
    set_kind("standalone")
    -- 定义交叉编译工具链地址
    set_sdkdir("~/work/wch_riscv/MRS_Toolchain_Linux_x64_V1.60/risc_v_embedded_gcc") --需要修改
    set_toolset("cc","riscv-none-embed-gcc")
    set_toolset("ld","riscv-none-embed-gcc")
toolchain_end()

target("test")
    -- 编译为二进制程序
    set_kind("binary") 
    -- 设置使用的交叉编译工具链
    set_toolchains("riscv-none-embed")
    -- 设置平台
    set_plat("cross")
    -- 设置架构
    set_arch("riscv")
    -- 设置目标文件的postname
    set_suffixname("_$(mode)")
    -- 设置目标文件的拓展名
    set_extension(".elf")

    add_defines(
        "CH32V20x_D6"
    )

    -- 添加链接库
    add_links("c", "m", "nosys"); --
    
    -- 添加启动文件
    add_files("./Startup/startup_ch32v20x_D6.S");
    
    -- 源文件路径
    local src_path = {
        "./User",
        "./Peripheral/src",
        "./Core",
        "./Debug",
    }
    -- 头文件路径
    local inc_path = {
        "./Peripheral/inc",
        "./User",
        "./Core",
        "./Debug",
    }

    -- 添加源文件路径
    for _, index in ipairs(src_path) do  -- 遍历 src_path
        add_files(index.."/*.c"); 
    end

    -- 添加头文件路径
    for _, inc in ipairs(inc_path) do   -- 遍历 inc_path
        add_includedirs(inc);
    end
   
    if is_mode("debug") then 
        add_cflags("-g", "-gdwarf-2")
    end

    add_cflags(
        "-Og",
        "-march=rv32imacxw",
        "-mabi=ilp32",
        "-mcmodel=medany",
        "-msmall-data-limit=8",
        "-mno-save-restore",
        "-fmessage-length=0",
        "-fsigned-char",
        "-ffunction-sections",
        "-fdata-sections",
        "-fno-common",
        {force = true}
    )

    add_asflags(
        "-x assembler",
        "-MMD",
        "-MP",
        {force = true}
    )

    add_ldflags(
        "-T ./Ld/Link.ld",
        "-nostartfiles",
        "-Xlinker",        
        "--gc-sections",
        "-Wl,-Map,$(buildir)/CH32V203.map",
        "-Wl,--print-memory-usage",
        "--specs=nano.specs",  
        "--specs=nosys.specs",
        {force = true}
    )

    after_build(function(target)
        cprint("Compile finished!!!")
        cprint("Next, generate HEX and bin files.")
        -- 设置编译链工具的路径
        local bsdk = "/home/mecono/work/wch_riscv/MRS_Toolchain_Linux_x64_V1.60/risc_v_embedded_gcc"

        local cobjcopy = bsdk .. "/bin/riscv-none-embed-objcopy"
        local csize = bsdk .. "/bin/riscv-none-embed-size"
        local bdir = target:targetdir()
        local bname = target:name()
        local cbin = bdir ..'/' .. bname .. '.bin'
        local chex = bdir ..'/' .. bname .. '.hex'
        -- 生成 bin hex 文件到目标文件夹
        os.runv(cobjcopy,{"-Oihex",target:targetfile(),chex})
        os.runv(cobjcopy,{"-Obinary",target:targetfile(),cbin})
        print("Generate hex and bin files ok!!!")

        print(" ");
        print("********************储存空间占用情况*****************************")
        os.execv(csize,{"-Bd",target:targetfile()})
    end)

     -- 设置自定义清理脚本
    on_clean(function (target)
        -- 仅删掉目标文件
        os.rm(target:targetfile())
        os.rm("$(buildir)")
    end)