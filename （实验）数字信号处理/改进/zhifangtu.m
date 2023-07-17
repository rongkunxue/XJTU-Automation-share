for i=1:10
    a=mistake(i,:)/sum(mistake(i,:))*100;
    A=bar(0:9,a);
    axis([-1,10,0,100])
    title(['数字',int2str(i-1),'误纳为其他数字的比率'])
    xlabel('数字')
    ylabel('比例')
    for j=1:length(pro)

        text(j-1,a(j),[num2str(a(j)),'%'],'VerticalAlignment','bottom','HorizontalAlignment','center','FontSize',9,'color','k','FontWeight','bold')

    end
    saveas(A,[int2str(i-1),'的误纳率.jpg'],'jpg');
end