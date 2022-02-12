{
                fprintf(fout, "%d              ", distance[i][j]);
                fprintf(fout2, "%d              ", predecessor[i][j]+1);
            }
            else
            {
                fprintf(fout, "%s              ", "I");
                fprintf(fout2, "%s              ", "N");
            }