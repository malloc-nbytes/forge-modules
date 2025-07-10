module Test

# This file requires EARL to be installed (https://github.com/malloc-nbytes/EARL/).
# If you do not have it, or just do not want it, run `test.sh` instead.

import "std/system.rl"; as sys

set_flag("-xe");

let files = sys::get_all_files_by_ext(".", "c");
println(f"Compiling: {files}");
files.foreach(|f| {
    let cmd = f"gcc -shared -fPIC -o {f}.so {f}";
    println(cmd);
    sys::cmd_onfail(cmd, |_|{
        println(f"Failed to compile!");
        exit(1);
    });
});

println("Done, all compiled successfully");
$"rm *.so";
