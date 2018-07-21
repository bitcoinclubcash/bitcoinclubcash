package LyokocoinABC

import jetbrains.buildServer.configs.kotlin.v2017_2.*
import jetbrains.buildServer.configs.kotlin.v2017_2.Project
import LyokocoinABC.buildTypes.*
import LyokocoinABC.vcsRoots.*


object Project : Project({
    uuid = "1ddf9a64-4576-455b-b8c5-1be776a90759"
    id = "LyokocoinABC"
    parentId = "_Root"
    name = "Lyokocoin-ABC"

    vcsRoot(LyokocoinABCGit)

    buildType(LyokocoinABCMasterLinux)
})
