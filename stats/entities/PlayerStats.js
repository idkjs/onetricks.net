import ChampionStats from './ChampionStats'

class _PlayerStats {
    constructor(summonerID, region) {
        this.summonerID = parseInt(summonerID)
        this.ChampionStats = []
        this.matchesProcessed = []
        this.region = region
    }

    load(playerStats) {
        this.summonerID = playerStats.summonerId
        this.ChampionStats = playerStats.champions.map(champion => {
            const c = ChampionStats()
            c.load(champion)
            return c
        })
        this.matchesProcessed = playerStats.matchesProcessed
        this.region = playerStats.region
    }

    editExistingChampion(championID, didWin, matchID) {
        const { ChampionStats } = this
        const i = ChampionStats.findIndex(({ id }) => id === championID)
        if (didWin) {
            ChampionStats[i].incrementWins()
        } else {
            ChampionStats[i].incrementLosses()
        }
        this.matchesProcessed.push(matchID)
    }

    pushChampion(ChampionStat, matchID) {
        const { ChampionStats } = this
        ChampionStats.push(ChampionStat)
        this.matchesProcessed.push(matchID)
    }

    containsChampion(championID) {
        const { ChampionStats } = this
        return ChampionStats.find(({ id }) => id === championID)
    }

    containsMatch(matchID) {
        const { matchesProcessed } = this
        return matchesProcessed.some(id => id === matchID)
    }

    doesNotContainMatch(matchID) {
        return !this.containsMatch(matchID)
    }

    asObject() {
        const { summonerID, ChampionStats, region } = this

        return {
            summonerId: summonerID,
            champions: ChampionStats.map(el => el.asObject()),
            matchesProcessed: this.matchesProcessed,
            region,
        }
    }
}

const PlayerStats = (summonerID, ChampionStats) =>
    new _PlayerStats(summonerID, ChampionStats)

export const loadPlayerStats = playerStats => {
    const p = new PlayerStats()
    p.load(playerStats)
    return p
}
export default PlayerStats
