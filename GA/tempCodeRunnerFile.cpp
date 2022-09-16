for (int i = pos1; i <= pos2; ++i){
        child[i] = parent2.chromosome[i];
        visited[parent2.chromosome[i]] = true;
    }