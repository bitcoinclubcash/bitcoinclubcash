package LyokocoinABC.vcsRoots

import jetbrains.buildServer.configs.kotlin.v2017_2.*
import jetbrains.buildServer.configs.kotlin.v2017_2.vcs.GitVcsRoot

object LyokocoinABCGit : GitVcsRoot({
    uuid = "57a40841-f1d2-44cc-8b04-843863b08cc6"
    id = "LyokocoinABCGit"
    name = "ssh://vcs@reviews.lyokocoinabc.org:2221/source/lyokocoin-abc.git"
    url = "ssh://vcs@reviews.lyokocoinabc.org:2221/source/lyokocoin-abc.git"
    branchSpec = """
        +:refs/heads/(*)
        +:refs/tags/(*)
    """.trimIndent()
    authMethod = uploadedKey {
        uploadedKey = "teamcity"
    }
})
