const std = @import("std");
const Build = std.build;

pub fn build(b: *Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "breaker",
        .optimize = optimize,
        .target = target,
    });
    exe.addCSourceFiles(&.{
        "src/ball.c",
        "src/bar.c",
        "src/brick.c",
        "src/collisions.c",
        "src/game.c",
        "src/input.c",
        "src/main.c",
        "src/map.c",
        "src/particle.c",
        "src/particle_list.c",
        "src/resource_manager.c",
        "src/text.c",
        "src/ui.c",
        "src/utils.c",
        "src/window.c",
    }, &.{
        "-std=c17",
        "-Wpedantic",
        "-Wall",
        "-Wextra",
        "-Wshadow",
    });

    exe.linkSystemLibrary("c");
    exe.linkSystemLibrary("SDL2");
    exe.linkSystemLibrary("SDL2_image");
    exe.linkSystemLibrary("SDL2_mixer");
    exe.linkSystemLibrary("SDL2_ttf");
    b.installArtifact(exe);

    const play = b.step("play", "Play the game");
    const run = b.addRunArtifact(exe);
    run.step.dependOn(b.getInstallStep());
    play.dependOn(&run.step);
}
